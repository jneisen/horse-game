class SpriteRenderer {
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Texture2D &texture, vec2 position,
			vec2 size = vec2(10.0f, 10.0f), float rotate = 0.f,
			vec3 color = vec3(1.0f));
	private
		Shader shader;
		unsigned int quadVAO;

		void initRenderData;
};
