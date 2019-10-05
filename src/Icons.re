module Sigma = {
  [@react.component]
  let make = () => {
    <svg
      xmlns="http://www.w3.org/2000/svg"
      width="24"
      height="24"
      viewBox="0 0 24 24">
      <path d="M0 0h24v24H0z" fill="none" />
      <path d="M18 4H6v2l6.5 6L6 18v2h12v-3h-7l5-5-5-5h7z" />
    </svg>;
  };
};

module Close = {
  [@react.component]
  let make = () => {
    <svg
      xmlns="http://www.w3.org/2000/svg"
      width="24"
      height="24"
      viewBox="0 0 24 24">
      <path
        d="M19 6.41L17.59 5 12 10.59 6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 12 13.41 17.59 19 19 17.59 13.41 12z"
      />
      <path d="M0 0h24v24H0z" fill="none" />
    </svg>;
  };
};
