open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;

let component = ReasonReact.statelessComponent("SimpleForm_TextInput");

let handleChange = (ctx, name, beforeUpdate, event) => {
  let value = U.getEventValue(event);
  let value2 = beforeUpdate(value);
  ctx.updateInput(name, value2);
};

let handleBlur = (ctx, name, _event) => ctx.sendInputBlur(name);

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             /* hack to work around initial context */
             if (List.length(ctx.schemas) > 0) {
               let schema = U.findSchemaByName(ctx.schemas, name);
               let state = U.findStateByName(ctx.formState.inputStates, name);
               /* before action is called to pre process value */
               let beforeUpdate = U.maybeFunc(beforeUpdate, x => x);
               let errors =
                 V.validateInput(schema, state, ctx.formState)
                 |> List.filter(x => x.isValid == false);

               <div className="SimpleForm_TextInput-container">
                 <label> (ReasonReact.string(schema.label)) </label>
                 <SimpleForm_ErrorMsg inputState=state errors />
                 <SimpleForm_Input
                   name
                   type_="text"
                   value=state.value
                   unsafeProps
                   onBlur=(handleBlur(ctx, name))
                   onChange=(handleChange(ctx, name, beforeUpdate))
                 />
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};