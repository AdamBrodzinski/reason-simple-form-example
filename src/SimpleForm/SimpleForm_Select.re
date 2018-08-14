open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_Select");

let make =
    (~name: string, ~options, ~unsafeProps=?, ~beforeUpdate=x => x, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           SimpleForm_Utils.inputApi(
             name, ({state, inputSchema, hasSubmitted, sendBlur, sendChange}) =>
             <div className="SimpleForm_Select-container">
               <label> (ReasonReact.string(inputSchema.label)) </label>
               <SimpleForm_ErrorMsg inputState=state hasSubmitted />
               (
                 <select
                   name
                   className="SimpleForm_Select"
                   onBlur=(_e => sendBlur())
                   onChange=(
                     event => {
                       let value: string = U.getEventValue(event);
                       let value2 = beforeUpdate(value);
                       sendChange(value2);
                     }
                   )>
                   (
                     U.mapReactList(options, (i, (label, value)) =>
                       <option
                         className="SimpleForm_Select-option"
                         key=(string_of_int(i))
                         value>
                         (ReasonReact.string(label))
                       </option>
                     )
                   )
                 </select>
                 |> U.insertProps(unsafeProps)
               )
             </div>
           )
         )
    </SimpleForm_Form.Context.Consumer>,
};