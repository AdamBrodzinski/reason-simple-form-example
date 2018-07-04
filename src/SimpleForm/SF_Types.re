type schemaItem = {
  name: string,
  label: string,
};

type formState = {submitted: bool};

type context = {
  formState,
  schemas: list(schemaItem),
};