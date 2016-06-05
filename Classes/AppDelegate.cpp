#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

// 設置OpenGL context 這個設置對所有平台都有效
void AppDelegate::initGLContextAttrs()
{
    // 設置openGL contrxt屬性，當前只能設置6個屬性
    GLContextAttrs glContextAttrs = {8,     // red
        8,     // green
        8,     // blue
        8,     // alpha
        24,    // depth
        8};    // stencil
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// 當應用程序啟動執行，遊戲程序啟動入口
// 在這裡我們啟動了第一個Scenes
// 在具體遊戲中，通常在這裡啟動Loading界面
bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化director(導演，負責場景切換等。掌控Scene的一切)
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("HungryHeroProject", Rect(0, 0, 1334, 755));
        director->setOpenGLView(glview);
    }
    
    // 取得設置螢幕大小適配相關的函數。
    // 第3引數 = 適配策略ResolutionPolicy(enum型)。
    // EXACT_FIT : 完全拉伸整個區域全屏，但是卻就連圖片精靈也會被拉伸，圖片顯示可能會被壓縮或著拉伸，不再保持原有橫比。
    // NO_BORDER : 顧名思義就是沒有黑邊。圖片在區域全部可見，不會扭曲，但可能會被【剪裁掉】。維持原來的橫縱比。
    // SHOW_ALL : 因為有黑邊問題因此幾乎【不能用】。圖片在選定的區域全部可見，不會扭曲，維持原來的縱橫比，但可能顯示邊界。
    // FIXED_HEIGHT、FIXED_WIDTH : 不會拉伸圖片精靈。固定高度，修改內部畫布的寬度、高度來適應設備的縱橫比。不會扭曲。
    director->getOpenGLView()->setDesignResolutionSize(1334,        // widget 寬
                                                       755,         // hight 高
                                                       ResolutionPolicy::NO_BORDER);
    
    // 在螢幕上顯示FPS數。
    // 開發階段建議開啟此設置，可以通過此對遊戲的性能有所瞭解。等遊戲正式發佈時再關閉此設置。
    director->setDisplayStats(true);
    
    // 設置FPS數，默認值1.0 / 60。
    director->setAnimationInterval(1.0 / 60);
    
    // 場景素材的位置。
    FileUtils::getInstance()->addSearchPath("res");
    
    // 創建startlayer的Scene，這是一個自動回收的對象
    // 自動類型變量，C++的新標準，本來要指定型，但現在可用auto。在賦值時，編譯器將會自動識別類型。
    auto scene = StartScene::createScene();
    
    // 通知director運行startLayer的Scene
    director->runWithScene(scene);
    
    return true;
}

// 當進入遊戲後台時會掉用此方法。
// 比如玩遊戲時按下home鍵 or 玩遊戲時電話打入直接顯示來電界面。
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // 如果你的遊戲用了sompleAudioEngine，必須在這裡進行暫停。
    // 代碼如下：SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// 當遊戲恢復到前台運行時會掉用此方法。
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // 如果你的遊戲用了sompleAudioEngine，必須在這裡進行暫停。
    // 代碼如下： SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
