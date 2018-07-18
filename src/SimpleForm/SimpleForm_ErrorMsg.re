open SimpleForm_Types;

let component = ReasonReact.statelessComponent("SimpleForm_ErrorMsg");

let make = (~inputState, ~errors, _ch) => {
  ...component,
  render: _self =>
    <div className="SimpleForm_TextInput-error">
      (
        if (inputState.dirty) {
          switch (errors) {
          | [] => ReasonReact.null
          | [error] => ReasonReact.string(error.message)
          | [error, ..._rest] => ReasonReact.string(error.message)
          };
        } else {
          ReasonReact.null;
        }
      )
    </div>,
};