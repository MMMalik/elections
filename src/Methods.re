module Dhondt = {
  type party('info) = {
    id: string,
    votes: int,
    info: 'info,
  };

  type result('info) = {
    id: string,
    seats: int,
    info: 'info,
  };

  type denom('info) = {
    id: string,
    denominator: int,
    votes: int,
    info: 'info,
  };

  let areFloatsEqual = (a: float, b: float, prec: float) => {
    abs_float(a -. b) <= prec;
  };

  let calculateDenominators = (seats: int, party: party('a)) =>
    List.map(
      denom =>
        {
          id: party.id,
          denominator:
            int_of_float(
              float_of_int(party.votes) /. float_of_int(denom) +. 0.5,
            ),
          info: party.info,
          votes: party.votes,
        },
      Utils.range(1, seats + 1),
    );

  let sortByDenominators = (denoms: list(denom('a)), seats: int) =>
    Utils.take(
      seats,
      List.sort(
        (denom1, denom2) =>
          if (denom2.denominator > denom1.denominator) {
            1;
          } else if (denom2.denominator === denom1.denominator) {
            denom2.votes > denom1.votes ? 1 : (-1);
          } else {
            (-1);
          },
        denoms,
      ),
    );

  let parseDenominators =
      (denoms: list(denom('a)), parties: list(party('a))) =>
    List.fold_left(
      (acc, party: party('a)) =>
        acc
        @ [
          {
            id: party.id,
            seats:
              List.filter(
                (denom: denom('a)) => denom.id === party.id,
                denoms,
              )
              ->List.length,
            info: party.info,
          },
        ],
      [],
      parties,
    );

  let filterBelowTresh = (parties: list(party('a)), threshold: int) => {
    let sum =
      List.fold_left(
        (acc: int, item: party('a)) => item.votes + acc,
        0,
        parties,
      );
    List.filter(
      (item: party('a)) =>
        sum > 0
          ? float_of_int(item.votes)
            /. float_of_int(sum) >= float_of_int(threshold)
            /. 100.0
          : false,
      parties,
    );
  };

  let calculateResults = (parties, seats, threshold) => {
    let filtered = filterBelowTresh(parties, threshold);

    calculateDenominators(seats)
    ->List.map(filtered)
    ->List.concat
    ->sortByDenominators(seats)
    ->parseDenominators(filtered);
  };
};
