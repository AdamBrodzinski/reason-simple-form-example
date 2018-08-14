open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_TextArea");

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           SimpleForm_Utils.inputApi(
             name, ({state, inputSchema, hasSubmitted, sendBlur, sendChange}) =>
             <div className="SimpleForm_TextArea-container">
               <label> (ReasonReact.string(inputSchema.label)) </label>
               <SimpleForm_ErrorMsg
                 inputState=state
                 hasSubmitted
                 errors=state.errors
               />
               (
                 <textarea
                   name
                   value=state.value
                   onBlur=sendBlur
                   onChange=(
                     event => {
                       let value: string = U.getEventValue(event);
                       let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
                       let value2 = beforeUpdate(value);
                       sendChange(value2);
                     }
                   )
                 />
                 |> U.insertProps(unsafeProps)
               )
             </div>
           )
         )
    </SimpleForm_Form.Context.Consumer>,
};