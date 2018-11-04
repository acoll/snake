let component = ReasonReact.statelessComponent("Header");

/* let styles = ReactDOMRe.Style.make(~marginRight="10px", ()); */
let styles =
  Css.[
    selector(
      "& > a",
      [
        color(red),
        marginRight(px(10)),
        opacity(0.5),
        backgroundColor(purple),
      ],
    ),
  ];

Js.log(styles);

let make = _children => {
  ...component,
  render: _self =>
    <div className=(Css.style(styles))>
      <Next.Link href="/"> <a> (ReasonReact.string("Home")) </a> </Next.Link>
      <Next.Link href="/about">
        <a> (ReasonReact.string("About")) </a>
      </Next.Link>
    </div>,
};