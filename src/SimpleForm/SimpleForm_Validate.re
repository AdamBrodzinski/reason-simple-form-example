open SimpleForm_Types;

let validateRequired = iState => {
  let isValid = iState.value |> String.trim |> String.length > 0;
  {isValid, kind: "required", message: "This field is required"};
};

let validateEmail = (iState, msg) => {
  /* minimal match: chars before @ chars after and a period */
  let regex = [%re {|/.+@.+\..+/i|}];
  let isValid = Js.Re.test(iState.value, regex);
  {isValid, kind: "email", message: msg};
};

let validateRegex = (iState, regex: Js.Re.t, msg) => {
  let isValid = Js.Re.test(iState.value, regex);
  {isValid, kind: "regex", message: msg};
};

let validateMin = (iState, amount, msg) => {
  let isValid = String.length(iState.value) >= amount;
  {isValid, kind: "regex", message: msg};
};

let validateMax = (iState, amount, msg) => {
  let isValid = String.length(iState.value) <= amount;
  {isValid, kind: "regex", message: msg};
};

let validateInput =
    (iSchema: schemaItem, iState: inputState, _fState: formState) =>
  switch (iSchema.validations) {
  | [] => []
  | _ =>
    iSchema.validations
    |> List.map(validateVariant =>
         switch (validateVariant) {
         | Required => validateRequired(iState)
         | Email =>
           let msg = "A valid email address is required";
           validateEmail(iState, msg);
         | EmailWithMsg(msg) => validateEmail(iState, msg)
         | Regex(pat, msg) => validateRegex(iState, pat, msg)
         | Min(amt) =>
           let msg = string_of_int(amt) ++ " or more characters are required";
           validateMin(iState, amt, msg);
         | Max(amt) =>
           let msg = string_of_int(amt) ++ " or more characters are required";
           validateMax(iState, amt, msg);
         }
       )
  };

let inputIsValid = (iSchema, iState, formState) =>
  validateInput(iSchema, iState, formState)
  /* |> inspect */
  |> List.filter(v => v.isValid == false)
  |> List.length == 0;