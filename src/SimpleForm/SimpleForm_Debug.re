open SimpleForm_Types;

let formatValidationResults = results =>
  results
  |> Array.of_list
  |> Array.map((er: validationResult) =>
       {"isValid": er.isValid, "kind": er.kind, "message": er.message}
     );

let formatInputStates = states =>
  states
  |> Array.of_list
  |> Array.map((x: inputState) =>
       {
         "name": x.name,
         "value": x.value,
         "valid": x.valid,
         "dirty": x.dirty,
         "errors": formatValidationResults(x.errors),
       }
     );

/** Convert form state to a JS object for better logging */
let formatFormState = (state: formState) => {
  "submitted": state.submitted,
  "isValid": state.isValid,
  "inputStates": formatInputStates(state.inputStates),
};