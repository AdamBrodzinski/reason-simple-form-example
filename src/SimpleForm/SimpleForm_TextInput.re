open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_TextInput");

let handleChange = (ctx, name, value) : unit => ctx.updateInput(name, value);

let handleBlur = (ctx, name, _event) => ctx.sendInputBlur(name);

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               <SimpleForm_TextLikeInput
                 name
                 className="SimpleForm_TextInput-container"
                 castType="string"
                 inputType="text"
                 onBlur=(handleBlur(ctx, name))
                 onChange=(handleChange(ctx, name))
                 beforeUpdate
                 unsafeProps
                 ctx
               />;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};