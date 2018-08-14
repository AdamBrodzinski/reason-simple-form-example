open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_Checkbox");

let handleChange = (name, ctx, beforeUpdate, event) => {
  let value = U.getEventIsChecked(event);
  let value = string_of_bool(value);
  let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
  let value2 = beforeUpdate(value);
  if (value2 == "" || U.isStringBool(value2)) {
    ctx.updateInput(name, value2);
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
           SimpleForm_Utils.inputApi(
             name, ({ctx, state, inputSchema, hasSubmitted}) =>
             <div className="SimpleForm_Checkbox-container">
               <SimpleForm_ErrorMsg
                 inputState=state
                 hasSubmitted
                 errors=state.errors
               />
               <label
                 className="SimpleForm_Checkbox-label"
                 htmlFor=(idPrefix ++ name)>
                 (
                   <input
                     name
                     type_="checkbox"
                     id=(idPrefix ++ name)
                     onChange=(handleChange(name, ctx, beforeUpdate))
                   />
                   |> U.insertProps(unsafeProps)
                 )
                 (ReasonReact.string(inputSchema.label))
               </label>
             </div>
           )
         )
    </SimpleForm_Form.Context.Consumer>,
};