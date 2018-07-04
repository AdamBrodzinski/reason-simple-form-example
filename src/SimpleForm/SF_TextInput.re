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
           ctx => {
             let formSchemaItems = ctx.schemas;
             /* Js.log("schema list");
                Js.log(formSchemaItems); */
             let input =
               <input
                 name
                 onChange=(
                   (event: formEvent) => {
                     let value = SF_Utils.getEventValue(event);
                     Js.log(value);
                     ctx.updateInput(name, value);
                   }
                 )
               />;
             let schema =
               formSchemaItems |> List.find((x: schemaItem) => x.name == name);
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