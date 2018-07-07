open SF_Types;
module U = SF_Utils;

type formEvent = ReactEventRe.Form.t;

let component = ReasonReact.statelessComponent("SF_TextInput");

let handleChange = (ctx, name, event: formEvent) => {
  let value = U.getEventValue(event);
  ctx.updateInput(name, value);
};

let make = (~name: string, ~unsafeProps=?, _children) => {
  ...component,
  render: _self =>
    <SF_Form.Context.Consumer>
      ...(
           ctx => {
             let schema = U.findSchemaByName(ctx.schemas, name);
             let state = U.findStateByName(ctx.formState.inputStates, name);
             let input =
               <input
                 name
                 onChange=(handleChange(ctx, name))
                 value=state.value
               />;
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