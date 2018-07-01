let component = ReasonReact.statelessComponent("SF_TextInput");
type formEv = ReactEventRe.Form.t;

let handleChange = (event: formEv) => {
  let foo = SF_Utils.getEventValue(event);
  Js.log(foo);
};

let make = (~name: string, ~dangerousDomProps, _children) => {
  ...component,
  render: _self =>
    <div className="sf-input-container">
      (
        ReasonReact.cloneElement(
          <input name onChange=handleChange />,
          ~props=dangerousDomProps,
          [||],
        )
      )
    </div>,
};