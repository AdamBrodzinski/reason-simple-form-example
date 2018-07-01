let component = ReasonReact.statelessComponent("SF_TextInput");
type formEv = ReactEventRe.Form.t;

let handleChange = (event: formEv) => {
  let value = SF_Utils.getEventValue(event);
  Js.log(value);
};

let make = (~name: string, ~unsafeProps=?, _children) => {
  ...component,
  render: _self => {
    let input = <input name onChange=handleChange />;
    <div className="sf-input-container">
      (
        switch (unsafeProps) {
        | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
        | None => ReasonReact.cloneElement(input, [||])
        }
      )
    </div>;
  },
};