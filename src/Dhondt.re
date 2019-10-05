type result = {
  i: int,
  name: string,
  value: int,
  color: string,
};

module Result = {
  [@react.component]
  let make = (~handleResultChange: result => unit, ~result: result) => {
    let (err, setErr) = React.useState(() => "");
    let handleNameChange = evt => {
      handleResultChange({...result, name: Utils.valueFromEvent(evt)});
    };
    let handleValueChange = evt => {
      setErr(_ => "");
      let value =
        switch (Utils.valueFromEvent(evt)->int_of_string) {
        | v =>
          v < 0
            ? {
              setErr(_ => "Please provide natural number");
              result.value;
            }
            : v
        | exception (Failure(_)) =>
          setErr(_ => "Please provide natural number");
          result.value;
        };
      handleResultChange({...result, value});
    };

    <div style={ReactDOMRe.Style.make(~margin="15px 0", ())}>
      <input
        style={ReactDOMRe.Style.make(
          ~padding="5px",
          ~margin="0 10px 0 0",
          (),
        )}
        placeholder="Party name"
        type_="text"
        value={result.name}
        onChange=handleNameChange
      />
      <input
        style={ReactDOMRe.Style.make(~padding="5px", ~marginRight="5px", ())}
        type_="number"
        value={string_of_int(result.value)}
        onChange=handleValueChange
      />
      <span
        style={ReactDOMRe.Style.make(~color=Theme.palette.primary.err, ())}>
        {React.string(err)}
      </span>
    </div>;
  };
};

let exampleResults = [
  {i: 0, name: "Party A", value: 2500, color: Theme.seatColor(0)},
  {i: 1, name: "Party B", value: 1500, color: Theme.seatColor(1)},
  {i: 2, name: "Party C", value: 2000, color: Theme.seatColor(2)},
  {i: 3, name: "Party D", value: 315, color: Theme.seatColor(3)},
];

[@react.component]
let make = () => {
  let (seatsToTake, setSeatsToTake) = React.useState(() => 100);
  let (threshold, setThreshold) = React.useState(() => 5);
  let (results, setResults) = React.useState(() => exampleResults);

  let handleSeatsToTakeChange = evt => {
    let newSeatsVal = Utils.valueFromEvent(evt)->int_of_string;
    setSeatsToTake(_ => newSeatsVal);
  };

  let handleThresholdChange = evt => {
    let newThreshVal = Utils.valueFromEvent(evt)->int_of_string;
    setThreshold(_ => newThreshVal);
  };

  let handleAddResult = _ => {
    setResults(currentResults => {
      let i =
        List.length(results) === 0 ? 0 : List.rev(results)->List.hd.i + 1;
      let result: result = {
        i,
        name: "",
        value: 0,
        color: List.length(results)->Theme.seatColor,
      };
      List.append(currentResults, [result]);
    });
  };

  let handleResultChange = (newResult: result) => {
    setResults(_ =>
      List.map(
        (result: result) =>
          compare(newResult.i, result.i) == 0 ? newResult : result,
        results,
      )
    );
  };

  let handleRemoveResultClick = (i: int, _) => {
    setResults(currentResults =>
      List.filter(result => result.i !== i, currentResults)
    );
  };

  let dhondt =
    List.map(
      (r: result): Methods.Dhondt.party(result) =>
        {id: string_of_int(r.i), votes: r.value, info: r},
      results,
    )
    ->Methods.Dhondt.calculateResults(seatsToTake, threshold);

  let vizResults =
    List.map(
      (d: Methods.Dhondt.result(result)): Viz.vizResult =>
        {seats: d.seats, name: d.info.name, color: d.info.color},
      dhondt,
    );

  <div style={ReactDOMRe.Style.make(~margin="30px 100px", ())}>
    <div>
      {React.string(
         "Provide results as natural numbers (e.g. 23400 instead of 23.4%).",
       )}
    </div>
    <div>
      {React.string(
         "D'hondt denominators are rounded to the nearest integer. Total number of votes is a tie breaker.",
       )}
    </div>
    <div style={ReactDOMRe.Style.make(~margin="25px 5px", ~width="100%", ~borderTop="1px solid", ())} />
    <div style={ReactDOMRe.Style.make(~display="flex", ())}>
      <div style={ReactDOMRe.Style.make(~flexBasis="50%", ())}>
        <div style={ReactDOMRe.Style.make(~margin="10px 0", ())}>
          <span> {React.string("Seats to take: ")} </span>
          <input
            style={ReactDOMRe.Style.make(
              ~border="none",
              ~padding="5px",
              ~marginRight="5px",
              (),
            )}
            type_="number"
            value={string_of_int(seatsToTake)}
            onChange=handleSeatsToTakeChange
          />
        </div>
        <div style={ReactDOMRe.Style.make(~margin="10px 0", ())}>
          <span> {React.string("Threshold (%): ")} </span>
          <input
            style={ReactDOMRe.Style.make(
              ~border="none",
              ~padding="5px",
              ~marginRight="5px",
              (),
            )}
            type_="number"
            value={string_of_int(threshold)}
            onChange=handleThresholdChange
          />
        </div>
        <div style={ReactDOMRe.Style.make(~margin="10px 0", ())}>
          {React.string(
             "Please enter election results below (party name / number of votes): ",
           )}
        </div>
        {List.map(
           result =>
             <div
               style={ReactDOMRe.Style.make(
                 ~display="flex",
                 ~alignItems="center",
                 (),
               )}
               key={string_of_int(result.i)}>
               <Result handleResultChange result />
               <div
                 onClick={handleRemoveResultClick(result.i)}
                 style={ReactDOMRe.Style.make(~cursor="pointer", ())}>
                 <Icons.Close />
               </div>
             </div>,
           results,
         )
         ->Array.of_list
         ->React.array}
        <button
          style={ReactDOMRe.Style.make(
            ~backgroundColor=Theme.palette.primary.base,
            ~color=Theme.palette.primary.text,
            ~padding="5px 15px",
            ~border="none",
            (),
          )}
          onClick=handleAddResult>
          {React.string("+ Add new result")}
        </button>
      </div>
      <div style={ReactDOMRe.Style.make(~flexBasis="50%", ())}>
        <Viz.Textual results=vizResults />
        <Viz.Seats results=vizResults />
      </div>
    </div>
  </div>;
};
