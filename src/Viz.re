type vizResult = {
  name: string,
  seats: int,
  color: string,
};

module Block = {
  [@react.component]
  let make = (~color: string) =>
    <div
      style={ReactDOMRe.Style.make(
        ~display="inline-block",
        ~width="15px",
        ~height="15px",
        ~backgroundColor=color,
        ~margin="3px",
        (),
      )}
    />;
};

module Seats = {
  [@react.component]
  let make = (~results: list(vizResult)) => {
    <div style={ReactDOMRe.Style.make(~margin="30px 0", ())}>
      {List.mapi(
         (n, result: vizResult) =>
           List.map(
             i =>
               <Block
                 key={string_of_int(n) ++ string_of_int(i)}
                 color={result.color}
               />,
             Utils.range(0, result.seats),
           ),
         results,
       )
       ->List.concat
       ->Array.of_list
       ->React.array}
    </div>;
  };
};

module Textual = {
  [@react.component]
  let make = (~results: list(vizResult)) => {
    <div style={ReactDOMRe.Style.make(~margin="30px 0", ())}>
      {List.mapi(
         (n, result) =>
           <div
             key={string_of_int(n)}
             style={ReactDOMRe.Style.make(
               ~display="flex",
               ~alignItems="center",
               (),
             )}>
             <div style={ReactDOMRe.Style.make(~margin="5px", ())}>
               <Block color={result.color} />
             </div>
             <div style={ReactDOMRe.Style.make(~margin="10px 0", ())}>
               <div> {React.string(result.name)} </div>
               <div>
                 {React.string(string_of_int(result.seats) ++ " seats")}
               </div>
             </div>
           </div>,
         results,
       )
       ->Array.of_list
       ->React.array}
    </div>;
  };
};
