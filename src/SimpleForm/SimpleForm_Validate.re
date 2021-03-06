open SimpleForm_Types;

let validateRequired = (iState, msg) => {
  let isValid =
    switch (iState.value) {
    | "false" => false
    | otherVal => otherVal |> String.trim |> String.length > 0
    };
  {isValid, kind: "required", message: msg};
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
  {isValid, kind: "min", message: msg};
};

let validateMax = (iState, amount, msg) => {
  let isValid = String.length(iState.value) <= amount;
  {isValid, kind: "max", message: msg};
};

let validateWithFunc = (func, iState, formState) => {
  let (isValid, msg) = func(iState, formState);
  {isValid, kind: "function", message: msg};
};

let validateInput =
    (iSchema: schemaItem, iState: inputState, formState: formState) =>
  switch (iSchema.validations) {
  | [] => []
  | _ =>
    iSchema.validations
    |> List.map(validateVariant =>
         switch (validateVariant) {
         | Required =>
           let msg = "This field is required";
           validateRequired(iState, msg);
         | RequiredWithMsg(msg) => validateRequired(iState, msg)
         | Email =>
           let msg = "A valid email address is required";
           validateEmail(iState, msg);
         | EmailWithMsg(msg) => validateEmail(iState, msg)
         | Regex(pat, msg) => validateRegex(iState, pat, msg)
         | MinLen(amt) =>
           let msg = string_of_int(amt) ++ " or more characters are required";
           validateMin(iState, amt, msg);
         | MinLenWithMsg(amt, msg) => validateMin(iState, amt, msg)
         | MaxLen(amt) =>
           let msg = string_of_int(amt) ++ " or less characters are required";
           validateMax(iState, amt, msg);
         | MaxLenWithMsg(amt, msg) => validateMax(iState, amt, msg)
         | Func(func) => validateWithFunc(func, iState, formState)
         }
       )
  };

let inputIsValid = (iSchema, iState, formState) =>
  validateInput(iSchema, iState, formState)
  |> List.filter((v: validationResult) => v.isValid == false)
  |> List.length == 0;

let isFormValid = (formState, schema) =>
  formState.inputStates
  |> List.map((iState: inputState) => {
       let iSchema = SimpleForm_Utils.findSchemaByName(schema, iState.name);
       inputIsValid(iSchema, iState, formState);
     })
  |> List.filter(b => b == false)
  |> List.length == 0;