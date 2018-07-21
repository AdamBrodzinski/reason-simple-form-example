open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_IntInput");

let handleChange = (ctx, name, beforeUpdate, event) => {
  let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
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
             if (List.length(ctx.schemas) > 0) {
               <SimpleForm_TextLikeInput
                 name
                 onBlur=(handleBlur(ctx, name))
                 onChange=(handleChange(ctx, name, beforeUpdate))
                 className="SimpleForm_IntInput-container"
                 inputType="text"
                 castType="int"
                 unsafeProps
                 ctx
               />;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};