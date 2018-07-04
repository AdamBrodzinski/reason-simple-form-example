open SF_Types;
type formEvent = ReactEventRe.Form.t;

let component = ReasonReact.statelessComponent("SF_TextInput");

let handleChange = (event: formEvent) => {
  let value = SF_Utils.getEventValue(event);
  Js.log(value);
};

let make = (~name: string, ~unsafeProps=?, _children) => {
  ...component,
  render: _self =>
    <SF_Form.Context.Consumer>
      ...(
           formSchemas => {
             Js.log("schema list");
             Js.log(formSchemas);
             let input = <input name onChange=handleChange />;
             let schema = formSchemas |> List.find(x => x.name == name);
             <div className="sf-input-container">
               <label> (ReasonReact.string(schema.label)) </label>
               (
                 switch (unsafeProps) {
                 | Some(props) =>
                   ReasonReact.cloneElement(input, ~props, [||])
                 | None => ReasonReact.cloneElement(input, [||])
                 }
               )
             </div>;
           }
         )
    </SF_Form.Context.Consumer>,
};