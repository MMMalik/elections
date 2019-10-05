module SystemWrapper = {
  [@react.component]
  let make = (~children) => {
    <div
      style={ReactDOMRe.Style.make(
        ~backgroundColor=Theme.palette.secondary.base,
        ~color=Theme.palette.secondary.text,
        ~fill=Theme.palette.secondary.text,
        ~padding="10px",
        (),
      )}>
      children
    </div>;
  };
};

module Welcome = {
  [@react.component]
  let make = () => {
    <div
      style={ReactDOMRe.Style.make(
        ~backgroundColor=Theme.palette.primary.base,
        ~color=Theme.palette.primary.text,
        ~fill=Theme.palette.primary.text,
        ~padding="20px",
        ~display="flex",
        ~alignItems="center",
        (),
      )}>
      <Icons.Sigma />
      {React.string("D'hondt Calculator")}
    </div>;
  };
};

[@react.component]
let make = () => {
  <div> <Welcome /> <SystemWrapper> <Dhondt /> </SystemWrapper> </div>;
};
