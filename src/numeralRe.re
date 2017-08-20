type float_or_str 'a =
  | Float :float_or_str float
  | String :float_or_str string;

module Numeral = {
  type t;
  external value : t => float = "value" [@@bs.send];
  external format : string => string = "" [@@bs.send.pipe : t];
  /* Functions */
  external clone : t = "" [@@bs.send.pipe : t];
  external mutableAdd : t => float => unit = "add" [@@bs.send];
  let add ::num numeral => {
    let clone = clone numeral;
    mutableAdd clone num;
    clone
  };
  external mutableSubtract : t => float => unit = "subtract" [@@bs.send];
  let subtract ::num numeral => {
    let clone = clone numeral;
    mutableSubtract clone num;
    clone
  };
  external mutableDivide : t => float => unit = "divide" [@@bs.send];
  let divide ::num numeral => {
    let clone = clone numeral;
    mutableDivide clone num;
    clone
  };
  external mutableMultiply : t => float => unit = "multiply" [@@bs.send];
  let multiply ::num numeral => {
    let clone = clone numeral;
    mutableMultiply clone num;
    clone
  };
  external difference : float => float = "" [@@bs.send.pipe : t];
};

external numeralDefaultFormat : (float_or_str 'a) [@bs.ignore] => 'a => Numeral.t =
  "numeral" [@@bs.module];

external numeralWithFormat : string => (float_or_str 'a) [@bs.ignore] => 'a => Numeral.t =
  "numeral" [@@bs.module];

let numeral ::format=? value =>
  switch format {
  | Some f => numeralWithFormat f value
  | None => numeralDefaultFormat value
  };