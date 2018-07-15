open SF_Types;
module U = SF_Utils;
module V = SimpleForm_Validate;

type formEvent = ReactEventRe.Form.t;
type b4u = option(string => string);

let component = ReasonReact.statelessComponent("SF_TextInput");

let handleChange = (ctx, name, beforeUpdate, event: formEvent) => {
  let value = U.getEventValue(event);
  let value2 = beforeUpdate(value);
  ctx.updateInput(name, value2);
};

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate: b4u=?, _ch) => {
  ...component,
  render: _self =>
    <SF_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               let schema = U.findSchemaByName(ctx.schemas, name);
               let state = U.findStateByName(ctx.formState.inputStates, name);
               /* before action is called to pre process value */
               let beforeUpdate = U.maybeFunc(beforeUpdate, x => x);
               let isValid = V.inputIsValid(schema, state, ctx.formState);
               <div className="SF_TextInput-container">
                 <label> (ReasonReact.string(schema.label)) </label>
                 <div>
                   (
                     isValid ?
                       ReasonReact.string("Valid") :
                       ReasonReact.string("Invalid")
                   )
                 </div>
                 <SF_Input
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
    </SF_Form.Context.Consumer>,
};