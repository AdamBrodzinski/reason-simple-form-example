open SF_Types;

type formEvent = ReactEventRe.Form.t;

let component = ReasonReact.statelessComponent("SF_TextInput");

let handleChange = (ctx, name, event: formEvent) => {
  let value = SF_Utils.getEventValue(event);
  ctx.updateInput(name, value);
};

let make = (~name: string, ~unsafeProps=?, _children) => {
  ...component,
  render: _self =>
    <SF_Form.Context.Consumer>
      ...(
           ctx => {
             let schema = SF_Utils.findSchemaByName(ctx.schemas, name);
             let state =
               SF_Utils.findStateByName(ctx.formState.inputStates, name);
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