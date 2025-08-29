export class Vector {

	/** @type { number } */ x;
	/** @type { number } */ y;
	/** @type { number } */ z;

};

/** @constant */
export class Shader {

	/** @type { string } */ source;
	/** @type { WebGLShader } */ id;

	/**
	 * @param { string } p_source
	 * @param { WebGLShader } p_id
	 */
	constructor(p_source = "", p_id) {
		this.source = p_source;
		this.id = p_id;
	}

};
