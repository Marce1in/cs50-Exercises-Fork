//É aqui onde é salvo e montado o txt da mensagens
let mensagens = '';


function observar(){
  //Seleciona o elemento que vai ser observado
  const elemento = document.querySelector("._3YS_f");
  //Configura para que seja observado todos os descendentes do elemento, ativando
  //apenas quando alguma texto é modificado
  const configuracao = {subtree: true, attributes: true};

  //Cria o objeto que vai ser usado para observar o elemento
  const observador = new MutationObserver(function(listaDeMudanças) {

    if (elemento.parentNode.style.getPropertyValue("pointer-events") === "none"){
      return;
    }
    //Quando o observador vê uma mudança ele salva essa mudança em uma lista
    //Esse loop passa por toda essa lista
    for(const mudança of listaDeMudanças) {

      console.log("tudo certo 1");
      console.log(mudança.target);
      //Verifica se isso é exatamente o texto que queremos
      if(mudança.attributeName !== "title"){
        return;
      }
      console.log("tudo certo 2");

      salvar_mensagem(mudança);

    }
  });

  //Aplicamos o objeto ao elemente, agora o elemento está sendo observado
  observador.observe(elemento, configuracao);
  //Sinalizamos que o programa está ativado
  console.log("O programa está ativado");
};

//Sobe nível a nível dos "divs" até chegar no desejado
function encontrar_ancestral(elemento, nivel){
  for (let i = 0; i < nivel; i++){
    elemento = elemento.parentNode
  }
  return elemento.previousElementSibling;
}

function salvar_mensagem (texto){
  //Encontra os ancestrais do texto
  const ancestral = encontrar_ancestral(texto.target.parentNode, 1);
  console.log("tudo certo 3");

  //Salvamos a mensagem
  const mensagem = texto.target.parentNode.textContent;
  console.log("tudo certo 4");
  //Usamos o ancestral para coletar o nome
  const nome = ancestral.children[0].children[0].textContent;
  console.log("tudo certo 5");
  //Pegamos a data atual do computador e separamos a hora, minutos e segundos
  const data = new Date().toLocaleTimeString();
  console.log("tudo certo 6");

  //Montamos uma linha de texto com todas as informações
  mensagens += '{"nome": "'+ nome +'", "data": "'+ data +'", "mensagem": "'+ mensagem +'"}\n';
  //Printamos a linha no console para verificar se está tudo certo
  console.log(mensagens);
}

observar();