//
// Created by cothrax on 12/24/19.
//

#ifndef FIVE_SCORES_H
#define FIVE_SCORES_H

#define MAX_PATTERN_NUM 100
#define MAX_PATTERN_SIZE 10
/*
20
111111		-100000		3		0		0
B11111B		100000		0		0		0
A22222A		-100000		0		0		0
B011110B	9050		2		0		0
022220		-9050		0		0		0
01111L		7000		2		1		1
B10111B		7000		2		1		1
B11011B		7000		2		1		0
B01110B		5000		1		0		0
02220		-5000		0		0		0
B011010B	4900		1		0		1
A022020A	-4900		0		0		1
B0101010B	1000		0		0		0
A0202020A	-1000		0		0		0
L11100B		1000		0		1		1
L01011B		1000		0		1		1
001100		90			0		1		0
B01100		90			0		1		1
00100		20			0		1		0
B01000		20			0		1		1
 */
int pattern_num = 20;
char score_patterns[MAX_PATTERN_NUM][MAX_PATTERN_SIZE] = {
        "111111",
        "B11111B",
        "A22222A",
        "B011110B",
        "022220",
        "01111L",
        "B10111B",
        "B11011B",
        "B01110B",
        "02220",
        "B011010B",
        "A022020A",
        "B0101010B",
        "A0202020A",
        "L11100B",
        "L01011B",
        "001100",
        "B01100",
        "00100",
        "B01000"
};
int score_ratings[MAX_PATTERN_NUM] = {-100000, 100000, -100000, 9050, -9050, 7000, 7000, 7000, 5000, -5000, 4900, -4900, 1000, -1000, 1000, 1000, 90, 90, 20, 20  };
int score_tags[MAX_PATTERN_NUM] = {3, 0, 0, 2, 0, 2, 2, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0  };
int score_can_flips[MAX_PATTERN_NUM] = {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1  };
int score_can_revs[MAX_PATTERN_NUM] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1  };

ull HASH_RANDS64[2][N][N] = {
        {
                {13415347395990201163ul, 1747136315003935741ul, 294706976190711923ul, 2955479027928125681ul, 8255313170671194484ul, 6452722333269582935ul, 17937990012732485599ul, 16062080394098890228ul, 3245217981973192584ul, 7435291187636587650ul, 3317830396500448504ul, 12098610704103095024ul, 11286679088380792507ul, 12068283166762355729ul, 13147213991135413406ul},
                {6713321905637157661ul, 9310663220879657874ul, 5693430632595174972ul, 16811659589251451183ul, 2975763593358016622ul, 14941493141405527225ul, 4693650456035054412ul, 4830534375225225193ul, 9484159420507062984ul, 1950668214282509596ul, 2916431988354523453ul, 4101284204644579183ul, 12962590222290919011ul, 3647448098778738509ul, 675502864883892300ul},
                {18135112412740770548ul, 16777766303930484146ul, 8013194626119832613ul, 1107199412257118427ul, 16048539508448740462ul, 501772082753615637ul, 11629937371906435384ul, 12220197979386935859ul, 800638382859699834ul, 7112162209017464181ul, 985876404664934214ul, 6408481909468648673ul, 3475457795094060910ul, 10293372257261744439ul, 9146776912943572231ul},
                {2854516190196852109ul, 1264982674378086719ul, 1630656893380185648ul, 7418540775763188ul, 9281582972731968017ul, 6986325853426077751ul, 18332422001640779984ul, 16096484975299922255ul, 476291125787613424ul, 1458108625610628082ul, 10936481733455452443ul, 10826786636792071455ul, 612208582791817530ul, 4580238024684157179ul, 12109850744006820641ul},
                {7336569534989752874ul, 2131043483945325866ul, 1745306115844650155ul, 8541268379129704657ul, 9588772371395335102ul, 590755783422214391ul, 7642795329647645842ul, 9875587873481485521ul, 1076967269902290243ul, 17904819488712625616ul, 7915094852212642233ul, 13705920306211725734ul, 16585308704560857229ul, 14221188742589391967ul, 2558721702970048306ul},
                {17208296172681499486ul, 6382030618439028869ul, 17513452274235254699ul, 4675388161500123310ul, 8752452296201533297ul, 10263350788461753543ul, 2963138484084003010ul, 1636270282814560248ul, 13412896682494335069ul, 17409153135659232704ul, 14894900422237899703ul, 12584051384473009291ul, 16277934115992070961ul, 7610423099568082566ul, 16183970069075566316ul},
                {785567050861584047ul, 13428662395308305462ul, 217608651563043191ul, 18210745444318886791ul, 5592883597174340070ul, 8690911836248811190ul, 12677882019491789666ul, 5141467938956132991ul, 3746186034858810353ul, 192508790523571899ul, 7408324030846242295ul, 14136484537480412012ul, 5870658590879008576ul, 3048653929735710630ul, 13600256447700801470ul},
                {3206740279488725977ul, 4257681483546574348ul, 4455229017765824283ul, 12839000976698855451ul, 16434113123735560175ul, 8411718243387078224ul, 12245785741435676963ul, 2081830383530605846ul, 12040118291451600747ul, 10727393190731215626ul, 10132275276948456524ul, 3766729996225664245ul, 14268947510509166199ul, 4918783902471627117ul, 1716518173830744627ul},
                {11661792979347945932ul, 13729113139796948347ul, 5209734524603098489ul, 429689882757343971ul, 6616176018872211914ul, 5475820093689531694ul, 809587786052699650ul, 13145489492245771876ul, 16259642013296255006ul, 16315777309102627402ul, 18440304236804491369ul, 2438400109228543272ul, 9715249869566064233ul, 6187578667219659560ul, 11083185965931261853ul},
                {14175635993506865079ul, 7967751099432216138ul, 10754138616241110607ul, 14699168930854173624ul, 1024092107866235676ul, 11746775406593189014ul, 17143155874693267377ul, 2636225127223715896ul, 9148579663254417999ul, 17237084022432199762ul, 12022964405463439782ul, 16263404103466757217ul, 1199760335095777016ul, 13347038692859701744ul, 14626908820484613610ul},
                {2631519641085952426ul, 2213635680415399071ul, 16523675115831293809ul, 7334860991782628460ul, 10019512591153360083ul, 10834718009896841010ul, 15366928859641037418ul, 14018507035842875161ul, 9967509155287587078ul, 1479245093611250949ul, 10636604507161583136ul, 7347876345122086197ul, 17742420857845709574ul, 14930250009192345942ul, 4817563388451101203ul},
                {9503126428576907951ul, 16183410911447120649ul, 5326445382767663158ul, 11342139969988550855ul, 14864046153563231043ul, 101014496345337634ul, 6313900610349570348ul, 13609763188073128850ul, 17749678884264615835ul, 13726721127709323351ul, 3436402788530653747ul, 13169857836884213620ul, 12753124355239267127ul, 13954154325480842896ul, 12086070789862871557ul},
                {9058901400596337244ul, 17926670938665220770ul, 3851723232899006475ul, 13251468695002880458ul, 13044992897904870770ul, 11469231014934926283ul, 9699918697135823180ul, 14019367661190576401ul, 12930759876682339405ul, 3237546059656974994ul, 15290369178737795253ul, 11998371047763735284ul, 17550825039379213154ul, 5943075054000567429ul, 7921241703627639260ul},
                {11208879774697578164ul, 6106048609865025797ul, 13103229206938855851ul, 3592902339489549760ul, 257730231662662652ul, 10142656232036847462ul, 13189279858543355370ul, 3354693282662378829ul, 6325448832731172949ul, 3352405254459815643ul, 15897356529649898993ul, 12044981025414121287ul, 1865860836975884635ul, 12748351221170094364ul, 10103053303114614323ul},
                {453349658847713300ul, 17261866301424911045ul, 15596930638757625133ul, 15237944246005594719ul, 6166005749292157720ul, 6771865077496686074ul, 13648445326465672081ul, 4183235450961399944ul, 11342237282964096557ul, 8348639152560141934ul, 17621611822430968038ul, 350087390227355271ul, 13057715102747968603ul, 15609599759560924656ul, 11985838000875779292ul}
        },
        {
                {13735353568741463687ul, 9170329753890714921ul, 11746403207488320643ul, 7229070789355540325ul, 10963666299866088197ul, 2899556129990802332ul, 14147116481872742560ul, 7087364637113641450ul, 974599402803981600ul, 18156233374225050909ul, 1667311843897014822ul, 4344059839816927851ul, 7708364801149330288ul, 12333084894665487810ul, 6565990788238822890ul},
                {4685379971784930793ul, 15513491860343023254ul, 14830153097226491317ul, 10756071716340348122ul, 8527589949719448863ul, 6884882967480511029ul, 12711149932897552694ul, 7535406641735690736ul, 17298785237390422854ul, 2258952250070671002ul, 6134295166803423177ul, 1583016223779778018ul, 13013297376881927278ul, 18002569761595725700ul, 12453865597610277820ul},
                {2148872297338763395ul, 17782542553133131190ul, 13978636401950423354ul, 6846126496868988785ul, 741815352460811328ul, 2635920659839178731ul, 14586745410445688792ul, 18341811953770822519ul, 17732350003736428846ul, 16521621886499162322ul, 14556150998793603263ul, 18327772672562135362ul, 995956833250303357ul, 6686762302234817015ul, 3101307953967967636ul},
                {525685623744354113ul, 17150087064958573791ul, 2844549801736294256ul, 17561551233046992430ul, 9163400657505944661ul, 16206570198243730343ul, 5209571669895753884ul, 3485862895035944103ul, 1002148278057228770ul, 17550060390310606427ul, 13692495848901932718ul, 6654635649028352622ul, 1505366778004286525ul, 14509790511690581104ul, 15328880960341781542ul},
                {11422414418219491667ul, 17657591296257171850ul, 16795953445074114486ul, 4946414067771327772ul, 11253959271664268313ul, 265364167812719550ul, 11761886875687390758ul, 10413048496988888222ul, 1881050962094205621ul, 9692390380512163710ul, 7362000624125734771ul, 10965628018247883148ul, 13474739426358416753ul, 17491102306311512815ul, 12692946238180100900ul},
                {492781461688120407ul, 7039041327944013681ul, 1284199414419059945ul, 802300478514271446ul, 12250649408160816493ul, 6449019094871450545ul, 14704180383808599090ul, 14139689680946262890ul, 15922076766819681575ul, 8776425356803736176ul, 8304888466387666440ul, 2318061942688243657ul, 5834941604443372243ul, 10301919348478601093ul, 4492114874667034757ul},
                {7471278549708489317ul, 7621173606355846387ul, 3960152680775240633ul, 14928976832932390874ul, 14729986940220729506ul, 2648720032690899284ul, 16586980690607747046ul, 8646775700248698755ul, 7479888076242451723ul, 16566807949819354909ul, 8947888252803124747ul, 2830963235009868165ul, 14997277455095208454ul, 2911190395870542945ul, 8257501289721504193ul},
                {13483410116000422610ul, 6174836134760162894ul, 14735414976913989082ul, 15479812572991667491ul, 2799375012912896312ul, 8658621039314834205ul, 8489773385686377063ul, 4190641186056436936ul, 7400825377258914232ul, 18141754860292229444ul, 17709976742701125993ul, 2743620077103690021ul, 12605353212957482672ul, 943662850163820070ul, 7000920252716467816ul},
                {11772064942389300482ul, 10624996280270348760ul, 1593723228715567909ul, 3565469910489401549ul, 7348979524482097109ul, 7506402040326425548ul, 15871215125035453879ul, 13367154497595017362ul, 915660214871978564ul, 5653323424100823627ul, 10538869731229486513ul, 5538444653667275597ul, 13515709470212994022ul, 7947075863951980403ul, 2562534321927443869ul},
                {1307258991938654842ul, 588602957864026076ul, 16503748521959025079ul, 2011247449336937805ul, 11239491022316015242ul, 4314062053318611305ul, 12138194096472025667ul, 15322820147145610851ul, 16185486516751965645ul, 12378022334359131137ul, 12600815307425219011ul, 6051780650713563754ul, 6900104607244810714ul, 7669781772468972107ul, 5933765486357723400ul},
                {17987937579338096165ul, 15099596118861281827ul, 16637524808521760786ul, 5914722702262854950ul, 14748112654902761509ul, 13566219096319249946ul, 12098969584986847779ul, 11791583996929759440ul, 9708168990033082638ul, 4215256672581907456ul, 3280770671911933350ul, 253656954426171969ul, 3065929267759670514ul, 6464704491873310235ul, 12736509090284508002ul},
                {18030663832658548805ul, 4672764915103686624ul, 15405002636604101684ul, 6852470632228773089ul, 7182684549173813307ul, 10044899000661607414ul, 240121090542640223ul, 10602535576605917333ul, 15503928683405061012ul, 1997410140351122573ul, 6570700331461293181ul, 15820100143166595277ul, 12546136993000085346ul, 11256639262132763543ul, 3535575815854340645ul},
                {17597770545218968827ul, 13887919007017869112ul, 917222413928748946ul, 3346904155140707407ul, 11725103579828445093ul, 8803580913332363355ul, 14277823740178644118ul, 17084987831080870767ul, 5820083513590661958ul, 13304768842271675781ul, 2187513667727214782ul, 27132468006990394ul, 8365877124120757895ul, 15075105318139513104ul, 6328094349805251745ul},
                {14222338421665413251ul, 9352502205182190868ul, 7495278053362356452ul, 12071444115019457585ul, 3093678749803416434ul, 5528694241690067516ul, 8200733786427289290ul, 15038931392984165997ul, 10473641313987921295ul, 1300901196151344856ul, 3432887152196764576ul, 16963475031633868552ul, 10934058149359124187ul, 13642460318583828039ul, 16093696959672340913ul},
                {3024760249385969835ul, 2704554189992183102ul, 262255364155726470ul, 8477942834212447339ul, 13091055494657113614ul, 12894687026171541877ul, 3842823098798301281ul, 16799814495415837875ul, 1814261195540927190ul, 4039587250818278597ul, 8523484869607656588ul, 13588490819317884572ul, 3061873995385700481ul, 12879154796690514217ul, 9035648030994253646ul}
        }
};

ull HASH_RANDS25[2][N][N] = {
        {
                {15346229, 4618355, 26580699, 31113583, 21422485, 25830181, 2015492, 28089409, 13431125, 19327057, 9248317, 30070244, 24449341, 1723728, 21502098},
                {12906907, 28313112, 33096739, 14412239, 14350601, 8671083, 29090619, 31048936, 10248062, 25382215, 23191775, 19249312, 10070295, 3990530, 8636483},
                {10706171, 29240594, 26770793, 4145982, 6551176, 29748209, 31913345, 12870752, 23075131, 2665004, 17129114, 12654541, 12814253, 13330335, 3973587},
                {6368965, 19497469, 15173827, 27303292, 9631787, 8031158, 24608709, 24266449, 27106113, 10884176, 7100924, 11386058, 10889974, 11920453, 26315704},
                {12521862, 6027221, 14010153, 29090900, 12465026, 27505978, 19308844, 17395388, 31450950, 4269612, 9029466, 19113433, 31351845, 20555284, 9766837},
                {2319208, 6292871, 3910923, 7018207, 17483488, 32835622, 32578351, 14992654, 1698921, 10003136, 19815546, 2653816, 12253235, 13083904, 23724969},
                {15857307, 11390564, 6091690, 3650195, 108080, 5537041, 7382092, 6744712, 6915616, 8596488, 9951399, 17678159, 13234662, 5954197, 8770716},
                {19329825, 4964198, 8156571, 2143022, 22066241, 15910575, 3459599, 4101360, 6059267, 23267177, 7059715, 32999989, 464885, 21181664, 10592567},
                {15514531, 52547, 19745944, 32223493, 14055327, 33352734, 25317972, 12139944, 4861917, 12723427, 23613343, 14816587, 24629227, 14798218, 26370004},
                {15404860, 2187291, 12083904, 19968714, 14483764, 22764416, 18063374, 9268749, 8782853, 22259040, 16768468, 7420350, 1798229, 30668387, 13697439},
                {4000354, 3318015, 8140273, 3040886, 6049583, 18786311, 8136393, 10636366, 8201230, 26316276, 14339856, 17970002, 31010313, 2469099, 12487777},
                {29884318, 17561183, 25668919, 15815504, 27425398, 33230157, 32615412, 5621049, 19036506, 4243610, 31407985, 8742617, 19330656, 29336662, 26240898},
                {21544185, 4471402, 10028776, 526723, 6086167, 3066982, 11526966, 31508214, 15144674, 12442054, 24679055, 2974386, 28262334, 24674010, 13025882},
                {29841361, 2930986, 8296797, 19774663, 27787026, 31959062, 16647726, 14338921, 28633002, 9037254, 7791504, 32331923, 8072719, 11694041, 10040291},
                {28230155, 8548719, 20290052, 5123774, 22686205, 23732114, 32657256, 22839435, 23330148, 17410711, 3321228, 30761716, 24832426, 11450757, 24179592}
        },
        {
                {16625061, 25664390, 23585669, 5818658, 11112404, 2141156, 1190395, 24423871, 3859917, 5957752, 3180333, 7602862, 24908684, 11417213, 11064487},
                {809439, 9447654, 31765979, 16797033, 19291501, 20115829, 12280916, 27797791, 11461747, 16513262, 6268825, 25489233, 7397979, 14424940, 21638661},
                {26080460, 32103876, 29493320, 23135887, 11555540, 2544448, 8602385, 7171979, 14921830, 5851832, 30707436, 7996489, 24844043, 22694863, 423596},
                {13248366, 8934499, 31212779, 22912920, 8694860, 21868505, 27152273, 19647715, 21587363, 2751131, 6207378, 23174281, 28885070, 23482356, 5445218},
                {18792819, 15475402, 1242801, 2507623, 28719812, 32896521, 32652793, 19276017, 10938203, 13756582, 9502969, 28943714, 7031668, 27860928, 5397347},
                {21140573, 9840576, 2674328, 24203713, 14246370, 29705367, 11919383, 17456074, 27698773, 30958395, 6769100, 14057762, 20406505, 6514863, 2241671},
                {25772004, 10114203, 2485570, 29532744, 27147561, 28102029, 32602289, 16855859, 29877568, 22699672, 4814092, 4078148, 28990975, 7311766, 24286162},
                {32782653, 3789869, 27097745, 11171188, 7241388, 12672142, 33006744, 26211472, 13931321, 24589627, 4063652, 19933161, 32513708, 6335839, 10079125},
                {16791656, 8366838, 28970488, 20575189, 3075874, 7710131, 10782763, 29250736, 29347338, 32772663, 19784686, 4012422, 7708624, 16570269, 13580765},
                {7041831, 11696426, 17065983, 31672212, 1409415, 10894100, 28565327, 32151060, 26629173, 8798229, 16321804, 5002031, 30931098, 30808795, 1996771},
                {717738, 27479192, 3236245, 20591724, 24466992, 14428008, 3111209, 21441429, 14442101, 918343, 6035381, 31336461, 12467682, 9079172, 4275315},
                {2591496, 27893627, 17557477, 15565687, 14547039, 14623929, 27742043, 7299096, 33429542, 20576161, 27221706, 27232379, 3258683, 30043593, 25319331},
                {11472584, 30636408, 3554616, 16751233, 23122182, 6950635, 12566918, 17290588, 6960546, 10161476, 7828236, 25394005, 6690481, 15629320, 20232882},
                {18558707, 31621252, 31801287, 28278493, 11596061, 16927815, 11369271, 2372739, 13915238, 15638806, 30410011, 3132347, 30268060, 9156237, 31129468},
                {3928289, 21501622, 14097844, 25048365, 33227526, 23850729, 32700620, 27740968, 28067849, 22674137, 12521725, 16725981, 13361719, 16715626, 11035360}
        }
};

#endif //FIVE_SCORES_H
