let valueFromEvent = evt => evt->ReactEvent.Form.target##value;

let rec range = (start: int, end_: int) =>
  if (start >= end_) {
    [];
  } else {
    [start, ...range(start + 1, end_)];
  };

let rec take = (n, list) =>
  switch (list) {
  | [] => []
  | [x, ...xs] => n == 0 ? [] : [x, ...take(n - 1, xs)]
  };
