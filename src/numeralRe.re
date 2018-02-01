type float_or_str('a) =
  | Float: float_or_str(float)
  | String: float_or_str(string);

module Numeral = {
  type t;
  [@bs.send] external value : t => float = "value";
  [@bs.send.pipe : t] external format : string => string = "";
  /* Functions */
  [@bs.send.pipe : t] external clone : t = "";
  [@bs.send] external mutableAdd : (t, float) => unit = "add";
  let add = (~num, numeral) => {
    let clone = clone(numeral);
    mutableAdd(clone, num);
    clone
  };
  [@bs.send] external mutableSubtract : (t, float) => unit = "subtract";
  let subtract = (~num, numeral) => {
    let clone = clone(numeral);
    mutableSubtract(clone, num);
    clone
  };
  [@bs.send] external mutableDivide : (t, float) => unit = "divide";
  let divide = (~num, numeral) => {
    let clone = clone(numeral);
    mutableDivide(clone, num);
    clone
  };
  [@bs.send] external mutableMultiply : (t, float) => unit = "multiply";
  let multiply = (~num, numeral) => {
    let clone = clone(numeral);
    mutableMultiply(clone, num);
    clone
  };
  [@bs.send.pipe : t] external difference : float => float = "";
};

[@bs.module]
external numeralDefaultFormat : ([@bs.ignore] float_or_str('a), 'a) => Numeral.t = "numeral";

[@bs.module]
external numeralWithFormat : (string, [@bs.ignore] float_or_str('a), 'a) => Numeral.t = "numeral";

let numeral = (~format=?, value) =>
  switch format {
  | Some(f) => numeralWithFormat(f, value)
  | None => numeralDefaultFormat(value)
  };
