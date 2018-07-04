type schemaItem = {
  name: string,
  label: string,
};

type context = {schemas: list(schemaItem)};

type formState = {submitted: bool};