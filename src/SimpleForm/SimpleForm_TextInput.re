open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;

type formEvent = ReactEventRe.Form.t;
type b4u = option(string => string);

let component = ReasonReact.statelessComponent("SimpleForm_TextInput");

let handleChange = (ctx, name, beforeUpdate, event: formEvent) => {
  let value = U.getEventValue(event);
  let value2 = beforeUpdate(value);
  ctx.updateInput(name, value2);
};

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate: b4u=?, _ch) => {
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
                 <div className="SimpleForm_TextInput-error">
                   (
                     if (state.dirty) {
                       switch (errors) {
                       | [] => ReasonReact.null
                       | [error] => ReasonReact.string(error.message)
                       | [firstE, ..._rest] =>
                         ReasonReact.string(firstE.message)
                       };
                     } else {
                       ReasonReact.string("not dirty");
                     }
                   )
                 </div>
                 <SimpleForm_Input
                   name
                   type_="text"
                   value=state.value
                   unsafeProps
                   onChange=(handleChange(ctx, name, beforeUpdate))
                 />
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};