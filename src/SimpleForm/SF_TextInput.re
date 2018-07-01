let component = ReasonReact.statelessComponent("SF_TextInput");

type formEv = ReactEventRe.Form.t;
type scItem = SF_Form.schemaItem;
type schemaList = list(SF_Form.schemaItem);

let handleChange = (event: formEv) => {
  let value = SF_Utils.getEventValue(event);
  Js.log(value);
};

let make = (~name: string, ~formSchema: schemaList, ~unsafeProps=?, _children) => {
  ...component,
  render: _self => {
    let input = <input name onChange=handleChange />;
    let schema = formSchema |> List.find((x: scItem) => x.name == name);
    <div className="sf-input-container">
      <label> (ReasonReact.string(schema.label)) </label>
      (
        switch (unsafeProps) {
        | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
        | None => ReasonReact.cloneElement(input, [||])
        }
      )
    </div>;
  },
};