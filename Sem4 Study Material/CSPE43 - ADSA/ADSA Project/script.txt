class Graph
{
    constructor(n, id, tableid)
    {
        this.v = n; // set number of vertices
        this.e = 0; // set number of edges
        this.points = []; // array of points
        this.edges = []; // array of edges
        this.matrix = []; // adjacency matrix
        this.labels = []; // vertices' labels
        this.table = document.getElementById(tableid);

        for (let i = 0; i < n; i++)
        {
            let row = [];
            for (let j = 0; j < n; j++) row.push(0);
            this.matrix.push(row);
        }

        this.c = document.getElementById(id); // canvas object
        this.ctx = this.c.getContext("2d");

        this.initPoints();
        this.refresh();
    }

    getMatrix()
    {
        return this.matrix;
    }

    initPoints()
    {
        let xc = 250, yc = 250, r = 200, t = (Math.PI*2)/this.v, a = 0;
        for (var i = 0; i < this.v; i++)
        {
            var x = xc + (r * Math.cos(a));
            var y = yc + (r * Math.sin(a));
            this.points[i] = {x:x, y:y, colour:"yellow", title:this.labels[i]};
            a += t;
        }
    }

    refresh()
    {
        this.plotPoints();
        this.drawEdges();
        this.draggable();
    }

    plotPoints()
    {
        this.ctx.clearRect(0, 0, this.c.width, this.c.height);

        for (var i = 0; i < this.v; i++)
        {
            this.ctx.beginPath();
            this.ctx.fillStyle = this.points[i].colour;
            this.ctx.arc(this.points[i].x, this.points[i].y, 15, 0, 2 * Math.PI);
            this.ctx.fill();
            this.ctx.stroke();

            this.ctx.fillStyle = "black";
            this.ctx.font = "bold 15px Arial";
            this.ctx.fillText(this.points[i].title, this.points[i].x-5, this.points[i].y+5);
        }
    }

    addVertex(code)
    {
        for (var i = 0; i < this.v; i++) this.matrix[i].push(0);

        this.v++;
        this.labels.push(code);
        
        let row = [];
        for (var i = 0; i < this.v; i++) row.push(0);
        this.matrix.push(row);

        this.initPoints();
        this.colourGraph();
    }

    drawEdges()
    {
        this.ctx.clearRect(0, 0, this.c.width, this.c.height); // clear current canvas
        this.plotPoints();

        for (var i = 0; i < this.v; i++)
            for (var j = 0; j < this.v; j++)
                this.matrix[i][j] = 0;

        for (var i = 0; i < this.e; i++)
        {
            let start = this.edges[i].start;
            let end = this.edges[i].end;

            this.ctx.beginPath();
            this.ctx.moveTo(this.points[start].x, this.points[start].y);
            this.ctx.lineTo(this.points[end].x, this.points[end].y);
            this.ctx.stroke();

            this.matrix[start][end] = this.matrix[end][start] = 1; // set in adjacency matrix
        }
    }

    addEdge(a, b)
    {
        this.edges.push({start: a, end: b});
        this.e++;
        this.refresh();
        this.colourGraph();
    }

    removeEdge(a, b)
    {
        for (var i = 0; i < this.e; i++)
        {
            if ((this.edges[i].start == a && this.edges[i].end == b) || (this.edges[i].start == b && this.edges[i].end == a))
            {
                this.edges.splice(i, 1);
                i--;
                this.e--;
            }
        }
        this.refresh();
        this.colourGraph();
    }

    aboutSame(x1, x2, y1, y2)
    {
        return (Math.abs(x1-x2) <= 10) && (Math.abs(y1-y2) <= 10);
    }

    draggable()
    {
        let obj = this;

        obj.c.onmousedown = function(event)
        {
            for (var i = 0; i < obj.v; i++) {
                let p = obj.points[i];
                var about = obj.aboutSame(p.x, event.clientX-obj.c.offsetLeft, p.y, event.clientY-obj.c.offsetTop);
                if (about)
                {
                    obj.c.onmousemove = function(eventmove)
                    {
                        p.x = eventmove.clientX-obj.c.offsetLeft;
                        p.y = eventmove.clientY-obj.c.offsetTop;
                        obj.c.style.cursor = "pointer";
                        p.colour = "orange";
                        obj.refresh();
                    }

                    obj.c.onmouseup = function(event)
                    {
                        obj.c.onmousemove = undefined;
                        obj.c.style.cursor = "default";
                        obj.colourGraph();
                        obj.refresh();
                    }
                }
            }
        }
    }

    completeGraph(vertices)
    {
        let n = vertices.length;
        for (var i = 0; i < n; i++)
            for (var j = i+1; j < n; j++)
                this.addEdge(vertices[i], vertices[j]);
    }

    colour()
    {
        let M = this.matrix;
        var c = 0; // current colour
        let colours = []; // length = number of vertices
        let v = M.length; // number of vertices

        for (var x = 0; x < v; x++)
            colours.push(-1); // no colour assigned initially

        for (var i = 0; i < v; i++)
        {
            var col = 0;

            while (true)
            {
                let flag = true; // positive assumption, current colour not adjacent

                for (let j = 0; j < v; j++)
                {
                    if (M[i][j] && colours[j] == col) // adjacent colour is same
                    {
                        flag = false; // trust broken
                        break; // no point continuing
                    }
                }

                if (flag) // trust preserved
                {
                    colours[i] = col; // set colour
                    break; // end search for current vertex
                }

                else // trust broken
                    col++; // continue with next colour
            }
        }

        return colours;
    }

    colourGraph()
    {
        let code = this.colour();
        const colours = ["red",  "green", "blue", "yellow", "pink", "violet", "grey", "white"];
        let arr = [];
        for (var i = 0; i < 10; i++) arr.push([]);
        for (var i = 0; i < this.v; i++)
        {
            this.points[i].colour = colours[code[i]];
            arr[code[i]].push(i);
        }
        this.refresh();

        this.table.innerHTML = "";
        for (let i = 0; i < arr.length; i++)
        {
            const row = document.createElement("tr");
            for (let j = 0; j < arr[i].length; j++)
            {
                const cell = document.createElement("td");
                cell.innerHTML = this.subj[arr[i][j]].subject;
                row.appendChild(cell);
            }
            this.table.appendChild(row);
        }
    }
}

class Subjects
{
    constructor()
    {
        this.G = new Graph(0, "shape", "timetable");
        this.G.subj = [];
        this.G.subjsno = [];
        this.table = document.getElementById("timetable");
    }

    add(s, c)
    {
        this.G.subj.push({subject: s, code: c, sno: this.G.v});
        this.G.subjsno.push(this.G.v);
        this.G.addVertex(c);
        this.G.completeGraph(this.G.subjsno);

        this.table.innerHTML = "";
        this.G.colourGraph(this.G.subj);
    }
    
    addEdge(code1, code2)
    {
        var a = -1, b = -1;
        for (var i = 0; i < this.G.subj.length; i++)
        {
            if (this.G.subj[i].code == code1) a = this.G.subj[i].sno;
            if (this.G.subj[i].code == code2) b = this.G.subj[i].sno;
        }
        this.G.addEdge(a, b);
    }

    remEdge(code1, code2)
    {
        var a = -1, b = -1;
        for (var i = 0; i < this.G.subj.length; i++)
        {
            if (this.G.subj[i].code == code1) a = this.G.subj[i].sno;
            if (this.G.subj[i].code == code2) b = this.G.subj[i].sno;
        }
        this.G.removeEdge(a, b);
    }
}

const obj = new Subjects();
document.getElementById("addS").onclick = function()
{
    let subject = prompt("Enter subject name : ");
    let code = prompt("Enter subject code : ");
    obj.add(subject, code);
};

document.getElementById("add").onclick = function()
{
    let code1 = prompt("Enter code of subject1 : ");
    let code2 = prompt("Enter code of subject 2 : ");
    obj.addEdge(code1, code2);
};

document.getElementById("remove").onclick = function()
{
    let code1 = prompt("Enter code of subject1 : ");
    let code2 = prompt("Enter code of subject 2 : ");
    obj.remEdge(code1, code2);
};