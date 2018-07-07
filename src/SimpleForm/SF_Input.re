/* component to clean up the handling of props and cloning */
let component = ReasonReact.statelessComponent("SF_Input");

let make = (~name, ~type_, ~value, ~unsafeProps, ~onChange, _children) => {
  ...component,
  render: _self => {
    let input = <input type_ name value onChange />;
    switch (unsafeProps) {
    | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
    | None => ReasonReact.cloneElement(input, [||])
    };
  },
};