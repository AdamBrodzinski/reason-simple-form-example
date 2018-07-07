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
             <div className="sf-input-container">
               <label> (ReasonReact.string(schema.label)) </label>
               <SF_Input
                 name
                 type_="text"
                 value=state.value
                 unsafeProps
                 onChange=(handleChange(ctx, name))
               />
             </div>;
           }
         )
    </SF_Form.Context.Consumer>,
};