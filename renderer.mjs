// This is what I'm gunna take inspiration from.

import { Shader, Vector } from "./utils.mjs";

/** Data for a model rendererd through a `Pipeline`. */
export class Model { };

/** A rendering pipeline to be run using a `Renderer`. */
export class Pipeline {

    step() { }

};

/** Stores and runs `Pipeline*` instances as instructed. */
export class Renderer {

    /** @type { WebGL2RenderingContext } */	gl;
    /** @type { HTMLCanvasElement } */		canvas;
    /** @type { Pipeline[] } */				pipelines;
    /** @type { number } */					frameRequestId;
    /** @type { number } */					lastFrameTimestamp;

    constructor({
        /** @type { Pipeline[] } */	pipelines: p_lines = [],
        /** @type { HTMLCanvasElement } */	canvas: p_canvas,
    }) {
        this.canvas = p_canvas;
        this.pipelines = p_lines;

        this.gl = this.canvas.getContext("webgl2");

        this.gl.clearColor(0, 0, 0, 0);

        this.frameRequestId = requestAnimationFrame(this.step.bind(this));
    }

    step(p_timestamp) {
        this.lastFrameTimestamp = p_timestamp;
        this.gl.clear(WebGLRenderingContext.COLOR_BUFFER_BIT | WebGL2RenderingContext.DEPTH_BUFFER_BIT);

        for (const p of this.pipelines) {

            p.step();

        }

        this.frameRequestId = requestAnimationFrame(this.step.bind(this));
    }

};

/** @extends { Model } */
export class ModelQuad {

    /** @type { Vector } */ color;
    /** @type { Vector } */ scale;
    /** @type { Vector } */ position;

};

let a = new Shader("", 0);

/** @extends { Pipeline } */
export class PipelineQuads {

    /** @type { WebGLBuffer } */ vbo;
    /** @type { Renderer } */ renderer;
    /** @type { number[] } */ vertices;
    /** @type { Shader } */ shaderVert;
    /** @type { Shader } */ shaderFrag;
    /** @type { ModelQuad[] } */ models;
    /** @type { WebGLProgram } */ program;
    /** @type { number[] } */ vboDeltaRanges;
    /** @type { WebGL2RenderingContext } */	gl;
    /** @type { WebGLVertexArrayObject } */ vao;

    constructor({
        /** @type { Renderer } */ renderer: p_renderer,
        /** @type { Shader } */ shaderVertex: p_shaderVert,
        /** @type { Shader } */ shaderFragment: p_shaderFrag,
        /** @type { number } */ preallocationCount: p_preallocs = 0,
    }) {
        this.renderer = p_renderer;

        this.gl = this.renderer.gl;
        this.vboDeltaRanges = new Set();
        this.renderer.pipelines.push(this);
        // this.models = new Array(p_preallocs);
        this.models = Array.from({ length: p_preallocs }, () => new ModelQuad());

        this.vbo = this.gl.createBuffer();
        this.vao = this.gl.createVertexArray();
        this.program = this.gl.createProgram();
        this.shaderVert = this.gl.createShader(WebGL2RenderingContext.VERTEX_SHADER);
        this.shaderFrag = this.gl.createShader(WebGL2RenderingContext.FRAGMENT_SHADER);

        /* Check out `ModelQuad` */
        this.gl.enableVertexAttribArray(0); // Color,
        this.gl.enableVertexAttribArray(1); // Scale,
        this.gl.enableVertexAttribArray(2); // Position.

        /* Yes, all of these are for each instance. */
        this.gl.vertexAttribDivisor(0, 0);
        this.gl.vertexAttribDivisor(1, 0);
        this.gl.vertexAttribDivisor(2, 0);

        // Color is attrib 0, has 3 `float`s, needs not be normalized,
        // has an offset of a 3-`float` vector per instance,
        // and the first entry is in the beginning of the array!
        this.gl.vertexAttribPointer(0, 3, WebGL2RenderingContext.FLOAT, false, 2 * 3 * 4, 2 * 3 * 0);

        // Scale is attrib 1, has 3 `float`s, needs not be normalized,
        // has an offset of a 3-`float` vector per instance,
        // and the first entry is in the beginning of the array!
        this.gl.vertexAttribPointer(1, 3, WebGL2RenderingContext.FLOAT, false, 2 * 3 * 4, 2 * 3 * 1);

        // Position is attrib 2, has 3 `float`s, needs not be normalized,
        // has an offset of a 3-`float` vector per instance,
        // and the first entry is in the beginning of the array!
        this.gl.vertexAttribPointer(2, 3, WebGL2RenderingContext.FLOAT, false, 2 * 3 * 4, 2 * 3 * 2);

        this.gl.attachShader(this.program, this.shaderVert);
        this.gl.attachShader(this.program, this.shaderFrag);
    }

    setFragmentShader(p_source) {

    }

    setVertexShader(p_source) {

    }

    step() {
        if (this.vboDeltaRanges.size() === 0) {

            return;

        }

        this.vboDeltaRanges.clear();
    }

    clean() {
        this.gl.deleteBuffer(this.vbo);
        this.gl.deleteProgram(this.program);
        this.gl.deleteVertexArray(this.vao);
        this.gl.deleteShader(this.shaderVert);
        this.gl.deleteShader(this.shaderFrag);
    }

};
