uniform sampler2D in_Texture;
uniform vec3 in_Emissive;
uniform vec3 in_Ambient;
uniform vec3 in_LightPos;
uniform vec3 lightPos;
uniform mat4 in_View;
varying vec2 ex_TexCoord;

varying vec3 ex_FragPos;
varying vec3 ex_Normal;

void main()
{
  vec3 norm = normalize(ex_Normal);
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  vec3 specular = spec * vec3(1,1,1);

  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * glm::vec3(0.5, 0.5, 0.5);
  //vec3 diffuse = diff * vec3(tex);

  vec3 lighting = in_Emissive + in_Ambient + diffuse + specular;
  gl_FragColor = tex * vec4(lighting, 1);
  //gl_FragColor = vec4(diffuse, 1);
}