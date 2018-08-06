open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;
/* component to clean up the handling of props and cloning */
let component = ReasonReact.statelessComponent("SimpleForm_TextLikeInput");

let make =
    (
      ~ctx,
      ~name,
      ~className,
      ~inputType,
      ~unsafeProps,
      ~onBlur,
      ~onChange,
      ~beforeUpdate,
      _children,
    ) => {
  ...component,
  render: _self => {
    let inputStates = ctx.formState.inputStates;
    let inputSchema = U.findSchemaByName(ctx.schemas, name);
    let inputState = U.findStateByName(inputStates, name);
    let hasSubmitted = ctx.formState.submitted;

    <div className>
      <label> (ReasonReact.string(inputSchema.label)) </label>
      <SimpleForm_ErrorMsg inputState hasSubmitted errors=inputState.errors />
      {
        let input =
          <input
            type_=inputType
            name
            value=inputState.value
            onChange=(
              event => {
                let value: string = U.getEventValue(event);
                let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
                let value2 = beforeUpdate(value);
                onChange(value2);
              }
            )
            onBlur
          />;
        switch (unsafeProps) {
        | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
        | None => ReasonReact.cloneElement(input, [||])
        };
      }
    </div>;
  },
};