type validationResult = {
  isValid: bool,
  kind: string,
  message: string,
};

type inputState = {
  name: string,
  value: string,
  valid: bool,
  dirty: bool,
  errors: list(validationResult),
};

type formState = {
  submitted: bool,
  loading: bool,
  isValid: bool,
  inputStates: list(inputState),
};

/** used to validate an input using custom logic */
type validateFunc = (inputState, formState) => (bool, string);

type validations =
  | Required
  | RequiredWithMsg(string)
  | Email
  | EmailWithMsg(string)
  | Regex(Js.Re.t, string)
  | MinLen(int)
  | MinLenWithMsg(int, string)
  | MaxLen(int)
  | MaxLenWithMsg(int, string)
  | Func(validateFunc);

type schemaItemType = [ | `String | `Float | `Int | `Bool];

/** Represents the schema for a single input */
type schemaItem = {
  name: string,
  castType: schemaItemType,
  initialValue: string,
  label: string,
  validations: list(validations),
};

type context = {
  formState,
  schemas: list(schemaItem),
  updateInput: (string, string) => unit,
  sendInputBlur: string => unit,
};