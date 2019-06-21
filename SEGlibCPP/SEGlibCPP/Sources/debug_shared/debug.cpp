#include <org/segames/library/core.h>
#include <org/segames/library/system.h>
#include <org/segames/library/math/vecmath.h>
#include <org/segames/library/exception.h>
#include <org/segames/library/util/timer.h>
#include <org/segames/library/gl/gl_pointer_inf.h>
#include <org/segames/library/glfw/glfw_window.h>
#include <org/segames/library/gl/gl_shader.h>
#include <org/segames/library/gl/gl_backed_buffer.h>
#include <org/segames/library/gl/gl_pointer_binding.h>
#include <org/segames/library/gl/gl_core.h>
#include <org/segames/library/gl/gl_exception.h>
#include <org/segames/library/gl/texture/gl_physical_texture_wrapper.h>
#include <org/segames/library/gl/fbo/gl_framebuffer_wrapper.h>
#include <org/segames/library/gl/text/gl_font.h>

#include <unordered_map>
#include <thread>
#include <iostream>


using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;
using namespace org::segames::library::glfw;
using namespace org::segames::library::gl;

int main()
{
	try
	{
		GLFWWindow win;
		win.setSize(1280, 800);
		win.setTitle("Library link test window");
		win.setVisible(true);
		win.makeContextCurrent();

		GLException::enableDebugCallback();

		GLShader shader;
		shader.loadVertexData("test/test.vert");
		shader.loadFragmentData("test/test.frag");
		shader.upload();

		GLPhysicalTextureWrapper tex("C:/Users/Philip R/Desktop/plan_flat.dds");
		tex.importTexture();
		tex.upload();

		GLFloatBuffer dou2;
		dou2.setPointerBinding(GLDataType::VERTEX, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.setPointerBinding(GLDataType::TEX_COORD, GLPointerInf(GL_FLOAT, 2, sizeof(GLfloat) * 2, 0));
		dou2.push(0).push(0);
		dou2.push(1).push(0);
		dou2.push(1).push(1);
		dou2.push(0).push(1);
		dou2.upload();

		//vvv TODO REMOVE THIS vvv
		ArrayList<unsigned int> chars;
		for (unsigned int i = 32; i < 127; i++)
			chars.add(i);
		//^^^ TODO REMOVE THIS ^^^

		GLFont font(20, 2, "test/times.ttf", chars.pointer(), chars.size());
		font.upload();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		bool lock = false;
		float count = 1;
		Timer rec;
		while (!win.isCloseRequested())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, win.getWidth(), win.getHeight());
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, win.getWidth(), win.getHeight(), 0, -1, 1);

			/*glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();*/

			/*font.getTexture()->bind();
			dou2.bind().setPointerInf();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			dou2.release();
			tex.release();*/

			font.render(0, 0, 
				"[L][o]rem ipsum dolor sit amet, consectetur adipiscing elit. Mauris eu risus rutrum, commodo tellus vitae, pretium massa. Quisque venenatis tempus efficitur. Nunc dictum, orci vitae euismod convallis, odio nulla sodales metus, dignissim venenatis purus ante vitae metus. In feugiat, quam id malesuada elementum, nibh ex porttitor lectus, et faucibus tortor erat eu elit. Nunc vel enim euismod nunc consectetur rutrum. Quisque congue a tortor vitae accumsan. Nam lacinia nulla ac nibh cursus, a pulvinar mi lacinia. Vestibulum iaculis nisl eget velit faucibus, sed viverra eros luctus. Etiam venenatis velit eget malesuada sodales. Duis in tincidunt lorem, id imperdiet dolor. Cras finibus, risus ac facilisis congue, odio velit hendrerit sem, sagittis fermentum tortor ex et lorem. Pellentesque nisi metus, rutrum in tristique eget, auctor ac lorem. Sed tempor odio vulputate fermentum vestibulum. Sed eget sapien rhoncus, volutpat ante vitae, dictum metus. Integer ac blandit velit.Maecenas eu tortor mollis, dignissim dolor eu, iaculis mauris. Donec pulvinar risus facilisis ante dignissim semper. Nullam lacinia vel justo in tincidunt. Cras in lobortis dolor, eu eleifend magna. Aliquam risus mauris, dapibus at luctus vitae, dignissim vel est. Proin mi turpis, maximus eget lacus in, congue dapibus purus. Suspendisse sit amet diam fringilla, feugiat felis non, venenatis massa. Curabitur tincidunt purus a dolor posuere volutpat. Suspendisse tristique nunc sit amet odio lobortis viverra. Curabitur finibus nisi sapien, a finibus elit egestas sed. In euismod ipsum nec sapien cursus, quis dapibus quam blandit. Suspendisse volutpat vehicula rutrum. Vestibulum vitae suscipit tortor, id tristique libero.Etiam id purus vitae mauris tincidunt consequat. Integer augue erat, suscipit sit amet quam sit amet, hendrerit ornare nisi. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Curabitur at mollis libero. Quisque tincidunt facilisis erat, eu tempor sem tempor sed. Nam placerat ligula nec lacinia condimentum. Nulla facilisi. Nunc luctus sem ut erat tempor laoreet. Nullam pulvinar dolor vitae ultrices tristique. Ut fringilla accumsan dolor, sit amet fermentum dui auctor eget.Duis cursus dictum sapien at pulvinar. Interdum et malesuada fames ac ante ipsum primis in faucibus. Donec in rutrum leo. Maecenas feugiat pharetra hendrerit. Cras id mollis ipsum. Integer pulvinar tempor elementum. Donec dictum est a odio faucibus accumsan. Aliquam vel interdum nunc, efficitur aliquam lorem. Curabitur elit ex, molestie eget tellus id, pulvinar ullamcorper tellus. Pellentesque dignissim rutrum fermentum. Pellentesque eleifend justo eu ipsum dictum, ac dapibus tortor convallis. Integer tempor est odio. Fusce ullamcorper quam et lobortis mattis.In lobortis bibendum eros, nec bibendum sem porta in. Donec faucibus justo risus, non sollicitudin ante pulvinar vel. Ut sem ante, tristique eu quam sed, iaculis bibendum ipsum. Ut vitae leo pharetra, malesuada arcu et, imperdiet ex. Donec ultricies justo in eros malesuada, vel rutrum diam bibendum. Integer euismod faucibus ex, a pulvinar arcu. Maecenas a sem nec dui volutpat congue.Fusce ut sapien est. Vivamus tristique leo ut pellentesque ornare. Vivamus maximus rutrum neque eget sagittis. In accumsan venenatis augue, eleifend eleifend nulla. Mauris venenatis at elit a posuere. Vivamus fringilla lorem vel tortor condimentum dapibus. Sed sit amet felis a risus cursus ultrices nec eget justo. Nunc interdum eget purus nec pulvinar. Aliquam vitae viverra magna. Fusce viverra augue sed dolor porttitor, et porttitor est consectetur.Sed interdum eget lorem quis rhoncus. Donec in diam eu elit pretium elementum id a ante. Vestibulum et tincidunt lacus, ut elementum lorem. Donec imperdiet, felis nec pulvinar maximus, nisl elit congue mi, id elementum nunc risus et enim. Curabitur sem ligula, congue ac libero vitae, interdum fermentum nisi. Nulla porttitor sit amet sem a euismod. Proin faucibus neque metus, non vestibulum enim aliquet et. Praesent a lectus dictum, malesuada lorem sit amet, convallis odio. Nullam nibh felis, lobortis et enim egestas, elementum egestas neque. Nunc placerat dui porttitor, ultrices mauris vitae, mollis elit.Nunc eget commodo nibh. Ut bibendum quis erat a ullamcorper. Suspendisse id orci urna. Pellentesque nunc tellus, fermentum sed dolor sed, placerat convallis augue. Nulla auctor, ante eu sodales pulvinar, justo orci volutpat arcu, non auctor lorem nunc vel augue. Nam quis urna vestibulum elit vestibulum gravida. Fusce at magna nec massa interdum suscipit. Sed iaculis justo ut velit facilisis, a lacinia mi sagittis. Quisque pellentesque arcu dui, vel laoreet massa bibendum ut. Morbi condimentum felis sit amet massa tempus, sed consectetur lacus commodo. Donec id vehicula enim. Sed varius, felis euismod pretium gravida, eros nisi pulvinar sapien, eu molestie nunc ligula non lorem.Aenean blandit dui tortor, at pulvinar arcu venenatis sed. Duis sit amet mollis lacus. Nam sollicitudin fermentum mi, eget consequat tortor sollicitudin vel. Suspendisse sit amet nibh eu augue finibus facilisis et sit amet nibh. Duis a metus faucibus, semper nibh vel, tempus ligula. Nam a ante quis libero condimentum porttitor. Praesent id leo efficitur, hendrerit justo eu, tempor lectus.Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris risus turpis, imperdiet vitae libero in, varius volutpat tortor. Nulla nec sem interdum, suscipit mauris vehicula, placerat mauris. Fusce sed nibh rutrum, facilisis metus et, lobortis augue. Proin et rutrum ligula. Morbi feugiat nisl quis aliquet venenatis. Sed posuere nisl at orci feugiat finibus.Praesent orci sapien, luctus id erat non, ornare aliquet nunc. Integer semper posuere ante rhoncus vestibulum. Duis sed augue consectetur, pretium felis quis, sollicitudin eros. Duis scelerisque nisl erat, nec gravida erat varius pellentesque. Fusce molestie elit lacus, in blandit tellus porttitor sed. Mauris ultricies posuere ullamcorper. Pellentesque id pretium purus. Proin blandit ante at odio interdum placerat. Aliquam condimentum nisl a leo placerat blandit. Nunc condimentum nibh id arcu consequat, ut semper mauris tincidunt. Suspendisse potenti. Phasellus eu porta nisl. Duis scelerisque velit ac leo consectetur imperdiet. Etiam dapibus blandit finibus.Vivamus auctor laoreet sagittis. Praesent enim risus, vulputate nec tincidunt vel, bibendum vitae mauris. Sed ac massa justo. Nunc vel magna porta, efficitur dui quis, suscipit ex. Nulla mattis congue mi nec placerat. Vestibulum malesuada semper sapien, eu iaculis nisl egestas eget. Ut ornare eget nulla at scelerisque.Integer tortor ante, commodo eu sapien et, ultricies rutrum odio. Nunc quis felis semper, auctor lectus at, commodo massa. In dictum turpis et ante dictum scelerisque. Curabitur lobortis risus dolor, sed porta sapien venenatis sit amet. Aenean in purus sit amet nunc ultrices consequat sit amet sed purus. Integer augue erat, ornare nec elit eget, viverra lacinia nulla. Quisque iaculis malesuada imperdiet. Nam rhoncus metus feugiat laoreet blandit. Etiam id mi nisi. Ut vestibulum vitae eros in cursus. Vivamus et tortor sem. In sit amet erat fermentum, ullamcorper massa vitae, iaculis nisi.Nulla vestibulum sapien quis aliquam porttitor. Duis congue ligula purus, vitae ultrices diam interdum nec. Donec non augue urna. Donec euismod dui felis, sit amet iaculis est condimentum et. Nam eget mi mi. Praesent dictum condimentum eleifend. Donec pretium ipsum quis magna rutrum, a mattis nunc rhoncus. Nulla facilisi.Etiam in nibh eleifend, interdum velit dignissim, porta ligula. Cras auctor odio non mauris commodo, at euismod ex scelerisque. Quisque rhoncus ullamcorper nulla et consequat. Aliquam ultrices a nunc quis mattis. Interdum et malesuada fames ac ante ipsum primis in faucibus. Proin efficitur eu lacus non consectetur. Ut justo tellus, finibus sed mattis eu, imperdiet quis ex. Donec ac convallis ante. Sed et diam ac tortor porttitor faucibus non semper augue. Praesent eget elit nisi. Aliquam erat volutpat.Suspendisse in scelerisque augue. Aenean et urna ac orci egestas sollicitudin. Proin eu diam eu ligula molestie tempus fringilla eu nisl. Donec fermentum sodales hendrerit. Aliquam sit amet dolor nulla. Nunc semper mi sit amet nibh elementum, in gravida lectus pretium. Aliquam tristique posuere turpis, euismod feugiat enim tristique sed. Etiam ut bibendum mauris. Nullam feugiat ante eget magna lacinia, commodo sagittis dolor placerat.Nulla sodales, ex sollicitudin bibendum convallis, elit ex elementum sem, vitae faucibus enim neque id mauris. Ut eget molestie est, et efficitur tortor. Fusce odio quam, consequat eu elit ut, pulvinar rutrum lectus. Maecenas laoreet pharetra placerat. Cras vel libero a ligula finibus sagittis ut sed tellus. Nulla euismod malesuada malesuada. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec ligula tortor, pharetra eget tempus eget, dictum nec lorem. Aenean rutrum iaculis dui, ac sodales turpis rhoncus ut. Fusce tortor elit, tincidunt at massa vitae, aliquet sagittis augue. Vivamus at tincidunt elit. Pellentesque vitae sagittis lacus. In posuere tincidunt orci in egestas.In hac habitasse platea dictumst. Curabitur lacus mauris, cursus non mauris euismod, tempus facilisis ipsum. Vestibulum a turpis lectus. Vestibulum dignissim, est ut sodales varius, ex risus tempus metus, eu interdum libero mi vitae nisl. Nulla sollicitudin lectus eu tincidunt viverra. Donec ante nulla, molestie nec mi quis, efficitur tincidunt lorem. Suspendisse blandit magna vitae augue rutrum, ut convallis enim ultricies. Duis eu mauris ipsum. Vestibulum non quam nec elit molestie bibendum sed sed sapien.Integer eget consequat nibh. Nunc imperdiet auctor est, sit amet mollis nulla suscipit nec. Quisque at nunc id dui hendrerit imperdiet sed at metus. Sed venenatis sagittis nibh, non cursus tellus fringilla a. Donec non tincidunt purus. Quisque ultricies purus sed tortor consectetur, blandit faucibus tellus dictum. Vivamus congue a ante id vehicula. Nullam vehicula suscipit ipsum. In ex ante, efficitur nec iaculis sed, luctus ac massa. Aenean aliquet vitae arcu et porta. Vestibulum ac pellentesque leo. Nunc erat arcu, vestibulum nec euismod nec, pretium eget velit. Pellentesque mattis tortor at porttitor consectetur. Nulla ac nibh eget mi dignissim dapibus sed at sem. Cras sed quam porttitor, suscipit dolor ac, tincidunt ante.Nam cursus volutpat odio ut interdum. In tristique imperdiet tellus et lacinia. Fusce ut libero interdum, facilisis nunc in, ultrices nibh. Mauris tincidunt eleifend congue. Aliquam vel nisi efficitur, bibendum nisi at, pulvinar ex. Aliquam a felis nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nulla ultricies accumsan elit id maximus. Nunc dapibus sapien id accumsan auctor. Phasellus mi est, tempor feugiat ante ut, aliquet varius diam. Sed ultrices sapien urna, vel posuere dolor faucibus id. Nulla sodales, nibh sed vulputate vulputate, augue velit laoreet augue, id facilisis lacus justo non dui. Nam sed orci et est molestie gravida. Nulla sed quam a lectus vulputate auctor vel nec magna. Maecenas aliquam quam quis ultricies vulputate.Phasellus at mauris id urna fermentum tempus. Phasellus a imperdiet lacus, et tempor elit. Nulla hendrerit sapien ac risus sollicitudin facilisis at at lorem. Integer neque justo, laoreet sed urna eu, sodales varius tellus. Mauris vulputate nunc non justo auctor, vitae tristique nulla fringilla. Aliquam et dui sed nibh lobortis interdum vestibulum eget risus. Vestibulum sit amet nunc vitae arcu commodo tempus. Donec consectetur ipsum diam, quis bibendum ipsum efficitur eu. Proin auctor dolor lorem, vitae tempor ipsum molestie ac. Mauris eget consequat lectus. Pellentesque eu quam semper, tempor magna vitae, tristique tortor. In leo metus, malesuada a augue a, scelerisque dapibus erat. Suspendisse purus turpis, posuere in pretium ac, convallis pharetra neque. Nam magna neque, pulvinar sit amet sollicitudin sit amet, condimentum ut nibh.Vestibulum interdum condimentum ipsum vitae interdum. Aenean turpis arcu, vehicula at elementum lobortis, consectetur in neque. Sed vehicula odio at justo pulvinar semper. Suspendisse facilisis vulputate ipsum, vel viverra ligula convallis in. Curabitur vel tellus id neque scelerisque viverra. Aliquam erat volutpat. Aenean laoreet pharetra est in vehicula. Mauris molestie, felis a scelerisque pharetra, urna lectus bibendum mi, eget lacinia tellus orci vel metus. Mauris volutpat placerat gravida. Mauris et mollis augue, eu semper mi. Nam scelerisque diam metus, nec dictum neque facilisis quis.Praesent eget finibus lacus. Aenean porta nunc non velit commodo placerat. Vivamus aliquam aliquet ligula, elementum aliquam enim venenatis quis. Nam eget ex odio. Nullam non ornare dolor. Praesent ullamcorper arcu in libero accumsan, a consectetur eros vehicula. Proin ac justo id velit efficitur suscipit vestibulum et ante. Nunc aliquam iaculis eros, sed ullamcorper magna viverra quis. Curabitur auctor, lorem et mollis ultrices, metus mauris iaculis felis, non hendrerit elit urna vel ex.Aenean viverra ante vel ipsum egestas, ut rhoncus risus viverra. Duis pharetra eget metus et fringilla. Nunc dolor eros, porta quis arcu quis, lobortis posuere metus. Sed convallis mollis nisl, sed ullamcorper justo efficitur et. Nulla laoreet nulla in purus convallis aliquam. Phasellus nec enim consequat, commodo velit ut, tempus metus. Morbi id tempor nulla.Phasellus sollicitudin gravida mauris, quis efficitur tortor molestie vel. Nullam porta ex tellus, et vehicula nisi aliquam eu. Aliquam id elementum sem. Sed facilisis massa in elementum mattis. Ut sit amet rhoncus metus. Sed lorem lectus, volutpat ac sem nec, semper euismod ligula. Nunc ullamcorper luctus neque id condimentum. Donec ultrices purus et tempus facilisis. Etiam pretium massa non sagittis blandit. Etiam sollicitudin purus pulvinar velit varius, ac viverra dolor maximus. Donec enim urna, dapibus sit amet erat ac, malesuada vehicula nunc. Aliquam sed lacus egestas, congue neque eget, tempor nisl. Pellentesque tristique ex quis erat fermentum tincidunt.Phasellus elit leo, aliquam eget purus ac, placerat scelerisque arcu. Proin bibendum ac diam in euismod. Integer ornare elit eget arcu convallis, ut consequat urna sodales. Ut tincidunt metus risus. Aliquam erat volutpat. Nullam convallis ligula velit, sit amet laoreet orci luctus eget. Mauris accumsan elit vel consequat rutrum. Praesent lectus purus, interdum nec ullamcorper eget, blandit vitae sapien. Nunc ultrices volutpat eros, vitae pharetra arcu facilisis id.Vivamus vel vulputate nunc. Praesent eros ante, porttitor eu quam ut, suscipit pulvinar felis. Aenean tristique ante id erat facilisis tempor eget et mauris. Nulla quis mollis leo, at elementum eros. Maecenas varius turpis eu tellus blandit ultricies. Nam pellentesque lacus neque, eget consequat risus ultricies sit amet. Quisque in ipsum quis urna tincidunt vulputate ac fermentum massa. Praesent eget pretium quam. Nunc lorem arcu, dignissim eu purus vitae, finibus semper ex. Maecenas pulvinar elit ut aliquet malesuada. In rhoncus dui nec placerat placerat. Aliquam erat volutpat.Suspendisse in semper odio. Mauris iaculis feugiat sapien, vel pharetra magna scelerisque vitae. Mauris in nibh ac ligula ultricies consequat vel eget enim. Sed fringilla, lorem nec vulputate hendrerit, sapien risus porta nisi, nec viverra est neque eu augue. Sed pharetra ipsum ac justo posuere, congue commodo lacus vulputate. Duis eros nulla, ultrices eu porttitor quis, facilisis at risus. Proin vel mauris a enim pharetra feugiat in sed elit. Fusce placerat sagittis auctor. Fusce gravida egestas leo vitae pellentesque. Nam eu massa at ante porta gravida in eget felis. Vestibulum sapien est, blandit vel aliquam nec, sollicitudin eget felis.Nullam euismod suscipit ipsum sit amet facilisis. Etiam hendrerit, ipsum non suscipit imperdiet, arcu quam convallis nisi, nec commodo elit risus nec felis. Praesent ex nisl, fermentum et rhoncus at, luctus non ante. Nullam eu arcu sapien. Nullam nec efficitur magna. In rhoncus ultricies nunc, quis accumsan libero laoreet vitae. Aenean sodales feugiat tortor non suscipit. Maecenas fermentum, quam ut blandit elementum, massa arcu pretium est, nec bibendum metus quam pretium magna. Pellentesque vel pretium velit, ut placerat diam.Mauris nisl ante, scelerisque vitae convallis rhoncus, gravida eget nibh. In hac habitasse platea dictumst. Pellentesque a nulla eu turpis dignissim porta in non orci. Cras congue lectus ipsum, id porttitor ex laoreet ut. Sed nec molestie sem, ac pellentesque nunc. Vivamus maximus neque eu nibh tempus, eu lacinia libero porttitor. Aenean euismod urna id nulla varius tincidunt.Pellentesque non mattis nunc. Phasellus ultricies felis lectus, vel sollicitudin neque faucibus sed. Cras euismod lorem fringilla enim tincidunt porttitor. Suspendisse est magna, congue at condimentum vitae, luctus non magna. Etiam accumsan est sem, nec rutrum erat iaculis nec. Curabitur consectetur, metus eu posuere consequat, risus lectus elementum felis, in tincidunt sem purus ac ex. Vestibulum egestas tristique tortor. Proin massa eros, pretium in facilisis ut, laoreet eu sem. Vivamus sed rhoncus sapien. Nunc posuere justo nec tellus blandit, id sollicitudin mi sodales. Ut risus sapien, consectetur nec vestibulum a, sollicitudin at purus. Etiam ut pellentesque tellus.Maecenas dictum augue vitae posuere viverra. Sed rutrum, nisi sit amet suscipit volutpat, risus neque aliquet ante, vitae malesuada metus leo quis erat. Pellentesque erat lorem, volutpat et risus at, condimentum pharetra mi. Curabitur venenatis vulputate sapien, id efficitur nulla mattis sit amet. Aenean nec lorem sit amet ante scelerisque imperdiet. Vestibulum urna dolor, accumsan eu pretium sit amet, luctus ac ex. Sed et nisl tellus. Morbi mattis augue ultrices iaculis molestie. Proin ultrices tempor massa, eu tincidunt enim pulvinar id. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque urna felis, aliquet sit amet ipsum non, tincidunt porttitor lacus. Duis maximus finibus finibus. Donec massa magna, tempus sit amet sapien vitae, dignissim venenatis tortor.Nulla turpis felis, gravida at magna quis, ultrices volutpat sapien. Integer interdum mollis auctor. Mauris blandit velit nec eros tristique, vel euismod massa eleifend. Curabitur in semper enim, suscipit rhoncus nibh. Sed a lorem pulvinar, commodo elit eu, ullamcorper tellus. Phasellus in tortor ultrices sapien pretium dignissim ac sed sapien. Vestibulum porttitor massa sed turpis ornare tristique. Fusce porttitor sollicitudin neque, in fermentum arcu feugiat vulputate. Vivamus egestas ligula metus, at semper nibh vehicula in. Sed bibendum ornare lectus nec malesuada. Maecenas interdum tortor quis congue convallis. Morbi sed ante non sapien rutrum tempor id vitae est. Vestibulum placerat quam ac nibh faucibus interdum.Morbi arcu orci, gravida a bibendum at, convallis quis orci. Maecenas semper vitae ipsum eget vestibulum. Nullam vel sem scelerisque, euismod est vitae, mollis mauris. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Quisque sed porttitor neque, aliquam ullamcorper elit. Cras nec ligula odio. Nunc aliquet urna eget nisi dapibus fringilla. Pellentesque vel vestibulum dolor, eu sagittis dui. Morbi a lacus sodales, posuere risus mattis, convallis diam. Curabitur metus erat, ultrices ut dapibus sit amet, bibendum id ligula. Nullam euismod nisi vitae eros blandit, sit amet mattis sapien cursus. Mauris vitae pretium odio, vel faucibus magna. Pellentesque malesuada nibh nec nulla imperdiet cursus. Quisque vitae fringilla elit. Vestibulum ac porttitor nulla, elementum pharetra lectus.Suspendisse eget fermentum purus, eget finibus nisi. Maecenas sit amet leo sit amet ipsum semper vestibulum. Curabitur viverra eleifend vestibulum. Nullam finibus, mauris quis consectetur rhoncus, nunc magna rhoncus purus, eu dapibus sapien massa id augue. Praesent nec lorem viverra, vehicula augue sed, sollicitudin velit. Curabitur non tellus vel arcu eleifend aliquet. Vivamus at quam a massa aliquam finibus aliquam vehicula sapien. Integer nec ipsum commodo, porttitor sem id, luctus quam. Suspendisse elementum dolor nisi, sed varius sem sollicitudin at. Integer augue mi, interdum tempus dolor eget, ornare tristique risus. Aenean faucibus, tellus eget ornare aliquet, orci magna gravida quam, et posuere turpis nisl blandit enim. Sed euismod mattis efficitur. Nunc at ex bibendum nisl cursus lobortis ut in est. Nam felis turpis, vestibulum ut massa sed, placerat egestas magna. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.Morbi eu lobortis justo. Integer vitae nibh pulvinar, malesuada erat cursus, gravida mi. Nulla facilisi. Nunc leo ipsum, pharetra non odio vel, auctor varius massa. Nulla auctor risus ex, vel suscipit felis maximus in. Interdum et malesuada fames ac ante ipsum primis in faucibus. Aliquam sodales ligula est, at commodo ipsum dapibus quis. Phasellus lacinia ut mi vel sagittis. Duis eu arcu venenatis, consequat tortor at, ornare dui. Nulla pharetra maximus augue, nec sagittis dolor efficitur ac. Phasellus sed vehicula ante.In in luctus massa, sit amet tempus nisl. Phasellus tincidunt auctor felis quis placerat. Curabitur sed magna efficitur, consequat ante non, egestas dui. Mauris metus nulla, lacinia ac sodales ac, semper ac erat. Aenean non justo venenatis urna malesuada ornare. Proin vestibulum auctor ante, eget vestibulum nisi cursus non. Nam id consequat nulla. Nulla nec nibh efficitur, malesuada sapien vitae, elementum urna. Aenean ut mauris quis orci mollis lobortis eu eget ex. Vestibulum id tincidunt tellus. Nullam id tortor ipsum. Aliquam pulvinar bibendum tellus, nec imperdiet mi. Sed ut consequat velit, vel vestibulum justo. Donec orci risus, vehicula sit amet elementum accumsan, blandit non quam. Aliquam nec semper nunc.Ut et purus fermentum, laoreet mi sed, tempus lacus. Integer ultrices facilisis nisl, et sollicitudin leo pretium vel. Nulla rhoncus a lectus quis sagittis. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Nulla iaculis arcu at metus malesuada tempor. Sed quis dui et dui viverra fermentum sed id turpis. Vestibulum vel nunc dictum, bibendum lorem et, suscipit nibh. Nulla euismod leo quam.Integer ultricies scelerisque leo at molestie. Mauris porta mattis justo, vitae aliquet ligula rhoncus nec. Donec dolor urna, rutrum nec tellus a, ultricies tempus orci. Phasellus at tempus massa, id eleifend felis. Sed posuere justo ut finibus aliquam. Suspendisse convallis convallis venenatis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse in purus ac ligula tristique ultrices. Nullam vitae viverra lacus, quis porta enim. Pellentesque sapien lectus, ultrices sit amet sem vel, porttitor ullamcorper quam. Fusce ac lacinia lorem, quis egestas neque. Nulla fermentum dolor eu accumsan mattis. Nunc ut purus id nisi pretium facilisis. Donec maximus, dolor quis luctus egestas, sapien leo bibendum risus, feugiat feugiat risus turpis a libero. Phasellus rutrum volutpat purus eget hendrerit. Quisque pharetra vitae ipsum vitae blandit.Donec a egestas magna, sit amet sodales nisl. Etiam a hendrerit lectus. Sed id finibus nunc. Fusce ut nulla leo. Mauris in posuere est. Nunc viverra, nisi nec egestas aliquam, nisl augue dignissim justo, ac mollis libero arcu viverra turpis. Suspendisse scelerisque elit ut consectetur imperdiet. Donec ut purus erat. Mauris vulputate vestibulum mi, vel porta nisl. Aliquam vitae mauris nec orci porttitor pharetra sed ut tortor. Ut vestibulum consectetur turpis id pulvinar. Suspendisse sit amet euismod justo, vel interdum tortor.Sed efficitur tristique porta. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Sed risus ipsum, finibus non nibh at, blandit vestibulum mauris. Etiam vitae diam in mi feugiat efficitur. Duis a purus sit amet eros rutrum luctus. Mauris aliquam risus sed nunc vulputate, laoreet faucibus tellus iaculis. Nam id tincidunt dolor. Etiam laoreet scelerisque mi vel dapibus. Phasellus in ante ut ipsum ornare posuere. Cras justo quam, malesuada in sodales a, iaculis ac lacus. Pellentesque facilisis ex at turpis tincidunt, eget porttitor nunc accumsan. Duis dapibus eu neque condimentum eleifend. Fusce sed efficitur mi.Phasellus faucibus vulputate efficitur. Donec mattis nulla in sagittis pellentesque. Cras sed massa vehicula, sollicitudin velit ac, tempus velit. Maecenas ut tortor porttitor, tristique metus blandit, iaculis est. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Quisque vitae sapien euismod eros bibendum sollicitudin. Maecenas ut viverra turpis, id commodo eros. Aenean erat dolor, tincidunt id interdum id, ultricies sed libero. Nam interdum consectetur turpis, et consectetur velit egestas quis.Morbi iaculis, ligula quis sagittis mollis, purus felis malesuada libero, sit amet euismod nisi lorem ut lectus. Pellentesque condimentum lacinia elit, id dapibus libero. Duis quis mi nec mauris tempus sagittis. Fusce malesuada nunc a maximus aliquam. Pellentesque et turpis odio. Pellentesque eu dignissim nunc. Proin eleifend suscipit ornare. In nulla dolor, rutrum sit amet sapien vitae, accumsan consequat enim.Morbi mollis lacinia consequat. Quisque vulputate pulvinar odio, nec tristique lectus rhoncus at. Pellentesque at enim tincidunt, tristique tortor a, ullamcorper lacus. Phasellus facilisis quis dui vel consectetur. Duis vestibulum, velit nec luctus porttitor, enim velit tempor dolor, eget consectetur dui eros in augue. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam id tincidunt velit. Cras odio est, egestas et ultrices elementum, elementum in dolor. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean commodo tempor neque id condimentum. Cras bibendum, elit at rhoncus efficitur, tortor ex convallis nisi, ut cursus orci quam in turpis. Fusce suscipit mauris ut velit venenatis rutrum. Suspendisse ornare, enim a sollicitudin mattis, lacus tortor feugiat magna, at hendrerit diam lacus id arcu. Nunc eu ante eget lectus sodales vulputate. Ut malesuada sapien vitae sagittis vulputate. Pellentesque auctor magna varius, finibus orci quis, luctus nunc.Aliquam pharetra pretium tristique. Integer sed ante vel enim scelerisque molestie. Nullam elementum et ex et lacinia. Sed rhoncus sodales dui at consequat. Morbi tincidunt nisi a metus dapibus, ut faucibus nulla fringilla. Quisque cursus in massa sodales ornare. Vestibulum nec placerat nisl. Integer risus nulla, congue non felis eget, venenatis congue felis. Etiam luctus urna in tellus bibendum scelerisque. Quisque dolor urna, mollis at nisl ac, laoreet finibus justo. Cras tempus a quam vel posuere. Duis in sapien urna. Sed consequat malesuada condimentum. Mauris porttitor diam in diam mattis blandit. Fusce mi odio, pretium a porta id, mattis non sapien. Morbi eget dapibus leo, id dapibus erat.Cras magna sem, facilisis eget nulla vel, tincidunt semper risus. Nulla purus sapien, pharetra ut magna at, lobortis facilisis lectus. Curabitur cursus turpis at dapibus ultrices. Nunc quis nibh orci. Nulla vitae dui lobortis, pharetra augue vitae, ullamcorper libero. Vivamus ac lorem malesuada, aliquam tellus vel, malesuada nisl. Quisque congue semper tincidunt. Integer et porttitor tellus. Aenean vestibulum risus leo. In tempus justo eu turpis vestibulum aliquet. Nunc libero nisl, malesuada quis urna eu, mattis elementum quam. Nulla in convallis massa, eleifend blandit dolor. Ut ut libero quis ipsum vehicula volutpat. Proin et sagittis risus. Aliquam fermentum varius erat, quis sollicitudin libero dapibus non. Pellentesque eget tellus sit amet erat ultricies mattis at ut odio.Duis nec ante mattis, cursus magna a, accumsan est. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Ut rhoncus bibendum nisl vel molestie. Donec scelerisque ex aliquam ligula viverra varius. Morbi placerat leo volutpat purus ultrices sodales. Ut sed tortor sem. Sed venenatis in arcu a egestas. Quisque eu nulla pulvinar, vulputate diam non, fermentum massa. Quisque vitae consectetur turpis.Aliquam eu mi eu purus consequat consequat eu quis tellus. Mauris in lacinia felis. Fusce sagittis eu lectus sed rutrum. Vivamus et egestas risus. Duis dapibus vestibulum justo, at hendrerit urna molestie in. Nunc luctus risus eu ligula luctus facilisis. Mauris consequat felis mi, at volutpat tortor convallis eleifend. Suspendisse potenti. Suspendisse venenatis quam non libero aliquet dapibus. Donec sit amet quam vel lectus accumsan porta. Suspendisse potenti. Nullam risus quam, sodales non neque a, egestas auctor lorem. Suspendisse ut commodo sapien. Vestibulum in venenatis lectus. Etiam aliquet risus at nunc facilisis, a porta magna gravida. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae;Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Donec ut lectus nisl. Fusce tincidunt, elit convallis aliquam hendrerit, eros elit congue lorem, vitae malesuada justo enim quis mauris. Fusce eu tempus tellus. Cras tincidunt justo quis turpis mollis condimentum. Donec facilisis pellentesque diam ut bibendum. Aenean vehicula tincidunt mi quis porttitor. Quisque tortor ex, vestibulum at odio ut, fringilla eleifend tortor. Donec non efficitur ipsum, sollicitudin aliquam orci. Nullam accumsan, lectus eu feugiat volutpat, ante ligula ullamcorper tortor, non tristique arcu ligula vel nisl. Sed nec porttitor mi. Cras fermentum sed nunc ac ultricies. Cras scelerisque et mi tempor mattis. Integer faucibus lectus at dignissim sollicitudin. Aenean sed malesuada magna. Sed posuere consequat tellus id dignissim.Etiam eget efficitur est. Vestibulum dictum lorem arcu, sed sagittis odio molestie ac. Donec ex urna, ullamcorper vitae dolor non, tempus bibendum urna. Nam interdum leo vel egestas viverra. Nam euismod dignissim nisl id pellentesque. Nam id nisi turpis. Nullam mattis nibh facilisis, porta enim sed, sodales ex. Quisque finibus dictum mi, nec ornare urna suscipit quis. Ut dictum arcu eget gravida accumsan. Ut nisl lacus, dapibus in lacus vel, cursus commodo mi. Cras blandit libero nec tempor rutrum. Etiam pharetra viverra pellentesque."
			);
			
			win.pollEvents();
			win.swapBuffers();

			if (count > 360)
				count = 0;
			else
				count += 0.05f;

			win.setTitle("Time: " + std::to_string(rec.deltaTime()) + "s");
		}

		std::cout << "Hello world!" << std::endl;
	}
	catch (Exception& e)
	{
		e.print();
	}

	return 0;
}