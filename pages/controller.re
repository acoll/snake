let component = ReasonReact.statelessComponent("Controller");

let controllerStyle =
  Css.[
    height(vh(100.)),
    display(grid),
    gridTemplateColumns([fr(1.), fr(1.), fr(1.)]),
    gridTemplateRows([fr(1.), fr(1.), fr(1.)]),
  ];

let pos = (x, y) =>
  Css.style(Css.[gridColumn(x + 1, x + 2), gridRow(y + 1, y + 2)]);

let make = _children => {
  ...component,
  render: _self =>
    ReasonReact.(
      <div className=(Css.style(controllerStyle))>
        <button className=(pos(1, 0))> (string("UP")) </button>
        <button className=(pos(1, 2))> (string("DOWN")) </button>
        <button className=(pos(0, 1))> (string("LEFT")) </button>
        <button className=(pos(2, 1))> (string("RIGHT")) </button>
      </div>
    ),
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));