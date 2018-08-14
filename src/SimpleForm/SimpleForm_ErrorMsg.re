open SimpleForm_Types;

let component = ReasonReact.statelessComponent("SimpleForm_ErrorMsg");

let make = (~inputState, ~hasSubmitted, _ch) => {
  ...component,
  render: _self =>
    <div className="SimpleForm_ErrorMsg">
      (
        if (hasSubmitted || inputState.dirty) {
          switch (inputState.errors) {
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