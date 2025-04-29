
function fmtStatus(game) {

  const s = game.getStatus();

  switch (s) {
    case Module.Status.RedPlay:   return "RedPlay";
    case Module.Status.BluePlay:  return "BluePlay";
    case Module.Status.RedWin:    return "RedWin";
    case Module.Status.BlueWin:   return "BlueWin";
    case Module.Status.Draw:      return "Draw";
  }

  return "UnknownStatus";
}

function setTitles(game, bot, h1) {
  const t = `Somegames (${game.getName()}, ${bot.getName()})`;
  document.title = t;
  h1.innerHTML = t;
}

function refresh(game, canvas, statusSpan) {

  statusSpan.innerHTML = fmtStatus(game);

  [ni, nj] = game.getSize();

  const width = canvas.width;
  const height = canvas.height;
  const di = height / ni;
  const dj = width / nj;
  const ctx = canvas.getContext("2d");

  if (game.isRunning())
    canvas.style.background = "green";
  else
    canvas.style.background = "grey";
  ctx.clearRect(0, 0, width, height);
  ctx.beginPath();

  // draw grid
  ctx.lineWidth = 3;

  for (let i = di; i < height; i += di) {
    ctx.moveTo(0, i);
    ctx.lineTo(width, i);
  }

  for (let j = dj; j < width; j += dj) {
    ctx.moveTo(j, 0);
    ctx.lineTo(j, height);
  }

  ctx.stroke();

  // draw cells

  const radius = Math.min(di, dj) * 0.5 - 10;
  const iToY = i => di * (ni - i - 0.5);
  const jToX = j => dj * (j + 0.5);

  const drawCells = function (vec, color) {
    ctx.fillStyle = color;
    for (let k=0; k<vec.size(); k+=1) {
      ctx.beginPath();
      [i, j] = vec.get(k);
      ctx.arc(jToX(j), iToY(i), radius, 0, 2 * Math.PI);
      ctx.fill();
    }
  }

  drawCells(game.getRedPosVec(), "red");
  drawCells(game.getBluePosVec(), "blue");

}

function handleClick(evt, game, bot, canvas, statusSpan) {

  if (game.isRunning()) {

    [ni, nj] = game.getSize();

    const width = canvas.width;
    const height = canvas.height;
    const di = height / ni;
    const dj = width / nj;
    const x = evt.offsetX;
    const y = evt.offsetY;
    const i = ni - 1 - Math.floor(y / di);
    const j = Math.floor(x / dj);

    // console.log(`click ${x} ${y} ${i} ${j}`);

    if (game.getStatus() == Module.Status.RedPlay || bot.isHuman()) {
      game.play([i, j]);
      refresh(game, canvas, statusSpan);
    }

    while (game.getStatus() == Module.Status.BluePlay && !bot.isHuman()) {
      const p = bot.genMove(game);
      game.play(p);
      refresh(game, canvas, statusSpan);
    }
    /*
    */

  }

}

function mkGame(name) {
  switch (name) {
    case "connectfour":   return new Module.Connectfour();
    case "gomoku7x9":     return new Module.Gomoku7x9();
    case "gomoku8x8":     return new Module.Gomoku8x8();
    case "reversi":       return new Module.Reversi();
    default:              return new Module.Tictactoe();
  }
}

function mkBot(name) {
  switch (name) {
    case "human":       return new Module.Human();
    case "random":      return new Module.Random();
    case "mc10k":      return new Module.Montecarlo(10000);
    default:            return new Module.Montecarlo(1000);
  }
}

