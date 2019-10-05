type scheme = {
  base: string,
  text: string,
  err: string,
};

type palette = {
  primary: scheme,
  secondary: scheme,
  tertiary: scheme,
};

let seats = ["#5825CC", "#776899", "#4772FF", "#FFD287", "#CC7925"];

let seatColor = (n: int) =>
  if (n < List.length(seats)) {
    List.nth(seats, n);
  } else {
    "#" ++ Random.int(16777215)->Js.Int.toStringWithRadix(~radix=16);
  };

let palette = {
  primary: {
    base: "#70789E",
    text: "#FFFFFF",
    err: "#FF0000",
  },
  secondary: {
    base: "#FFFFFF",
    text: "#70789E",
    err: "#FF0000",
  },
  tertiary: {
    base: "#2541CC",
    text: "#FFFFFF",
    err: "#FF0000",
  },
};
