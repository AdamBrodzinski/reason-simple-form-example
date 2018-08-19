[%bs.raw {|require('./SimpleForm/SimpleForm.css')|}];
open SimpleForm;

let component = ReasonReact.statelessComponent("SignupForm");

let isAge18AndUp = (inputState: SimpleForm_Types.inputState, _formState) => {
  let num = SimpleForm_Utils.intOfStringOrZero(inputState.value);
  let isValid = num >= 18;
  (isValid, "You must be over 18");
};

let formSchema: list(SimpleForm_Types.schemaItem) = [
  {
    name: "firstName",
    castType: `String,
    label: "First name",
    validations: [Required, MinLen(2)],
  },
  {
    name: "age",
    castType: `Int,
    label: "Age",
    validations: [Func(isAge18AndUp)],
  },
  {name: "income", castType: `Float, label: "Income", validations: []},
  {
    name: "moreInfo",
    castType: `String,
    label: "More Info",
    validations: [MinLen(5)],
  },
  {
    name: "gender",
    castType: `String,
    label: "Gender",
    validations: [Required],
  },
  {name: "plan", castType: `String, label: "Plan", validations: [Required]},
  {
    name: "subscribe",
    castType: `String,
    label: "Subscribe to Newsletter",
    validations: [],
  },
];

let make = _children => {
  let handleSubmit = (~sendLoaded, formState) => {
    Js.log(SimpleForm_Debug.formatFormState(formState));
    Js.Global.setTimeout(() => sendLoaded(), 1500);
  };

  {
    ...component,
    render: _self =>
      <div className="SignupForm">
        <Form schema=formSchema onSubmit=handleSubmit>
          <Input name="firstName" />
          <Input name="age" />
          <Input name="income" />
          <TextArea name="moreInfo" />
          <Radio
            name="gender"
            radioValues=[
              ("Male", "male"),
              ("Female", "female"),
              ("Trans", "trans"),
            ]
          />
          <Select
            name="plan"
            options=[("Select Plan", ""), ("Bronze", "plan1")]
          />
          <Checkbox name="subscribe" />
          <Submit text="Update" />
        </Form>
      </div>,
  };
};