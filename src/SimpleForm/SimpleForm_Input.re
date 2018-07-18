/* component to clean up the handling of props and cloning */
let component = ReasonReact.statelessComponent("SimpleForm_Input");

let make =
    (~name, ~type_, ~value, ~unsafeProps, ~onChange, ~onBlur, _children) => {
  ...component,
  render: _self => {
    let input = <input type_ name value onChange onBlur />;
    switch (unsafeProps) {
    | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
    | None => ReasonReact.cloneElement(input, [||])
    };
  },
};