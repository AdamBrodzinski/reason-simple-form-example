open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;

type formEvent = ReactEventRe.Form.t;
type beforeFn = option(string => string);

let component = ReasonReact.statelessComponent("SimpleForm_IntInput");

let handleChange = (ctx, name, beforeUpdate, event: formEvent) => {
  let value = U.getEventValue(event);
  let value2 = beforeUpdate(value);
  if (value2 == "" || U.isStringInteger(value2)) {
    ctx.updateInput(name, value2);
  };
};

let handleBlur = (ctx, name, _event) => ctx.sendInputBlur(name);

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             /* if statement to hack around initial context being empty on 1st render */
             if (List.length(ctx.schemas) > 0) {
               let inputStates = ctx.formState.inputStates;
               let inputSchema = U.findSchemaByName(ctx.schemas, name);
               let inputState = U.findStateByName(inputStates, name);
               let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
               let errors =
                 V.validateInput(inputSchema, inputState, ctx.formState)
                 |> List.filter(x => x.isValid == false);

               <div className="SimpleForm_IntInput-container">
                 <label> (ReasonReact.string(inputSchema.label)) </label>
                 <SimpleForm_ErrorMsg inputState errors />
                 <SimpleForm_Input
                   name
                   type_="text"
                   value=inputState.value
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