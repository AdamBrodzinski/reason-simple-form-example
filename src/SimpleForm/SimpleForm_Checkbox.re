open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_Checkbox");

let handleChange = (ctx, name, value) : unit => {
  if (value == "" || U.isStringBool(value)) {
    ctx.updateInput(name, value);
  };
  /* send blur to trigger a 'dirty' state */
  ctx.sendInputBlur(name);
};

let make =
    (~name: string, ~idPrefix="SF_", ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               let inputStates = ctx.formState.inputStates;
               let inputSchema = U.findSchemaByName(ctx.schemas, name);
               let inputState = U.findStateByName(inputStates, name);
               let hasSubmitted = ctx.formState.submitted;

               <div className="SimpleForm_Checkbox-container">
                 <SimpleForm_ErrorMsg
                   inputState
                   hasSubmitted
                   errors=inputState.errors
                 />
                 <label
                   className="SimpleForm_Checkbox-label"
                   htmlFor=(idPrefix ++ name)>
                   {
                     let input =
                       <input
                         id=(idPrefix ++ name)
                         type_="checkbox"
                         name
                         onChange=(
                           event => {
                             let value = U.getEventIsChecked(event);
                             let value = string_of_bool(value);
                             let beforeUpdate =
                               U.fallbackFunc(beforeUpdate, x => x);
                             let value2 = beforeUpdate(value);
                             handleChange(ctx, name, value2);
                           }
                         )
                       />;

                     switch (unsafeProps) {
                     | Some(props) =>
                       ReasonReact.cloneElement(input, ~props, [||])
                     | None => ReasonReact.cloneElement(input, [||])
                     };
                   }
                   (ReasonReact.string(inputSchema.label))
                 </label>
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};