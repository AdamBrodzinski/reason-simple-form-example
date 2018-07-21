/** Module allow most common functions to be opened all the time */

type textInput =
  | String(string)
  | Int(int)
  | Float(float);

let text = (arg: textInput) =>
  (
    switch (arg) {
    | Int(num) => string_of_int(num)
    | Float(num) => string_of_float(num)
    | String(txt) => txt
    }
  )
  |> ReasonReact.string;