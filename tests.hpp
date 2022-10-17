#include <iostream>
#include <iomanip>
#include "./LongInt/LongInt.hpp"

#define COM_WIDTH 15

// Let's create casual tests (because I have no time to add GoogleTesting :))
void set_tests()
{
	std::cout << std::boolalpha << std::left << std::hex;
}

void print_test(const std::string& test_name, const LongInt& a, const LongInt& b, const LongInt& sum,
                 const LongInt& diff, const LongInt& mult, const LongInt& mult_div,
                  const LongInt& sum_res, const LongInt& diff_res, const LongInt& mult_res,
                   const LongInt& mult_div_res)
{
    std::cout << "--------------------------------" << test_name << "--------------------------------\n";
    std::cout << std::setw(COM_WIDTH) << "A: " << a << std::endl;
    std::cout << std::setw(COM_WIDTH) << "B: " << b << std::endl;
    std::cout << "\nA + B: \n";
    std::cout << std::setw(COM_WIDTH) << "Predicted: " << sum << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Calculated: " << sum_res << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Equal: " << (sum == sum_res);
    std::cout << "\n\nA - B: \n";
    std::cout << std::setw(COM_WIDTH) << "Predicted: " << diff << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Calculated: " << diff_res << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Equal: " << (diff == diff_res);
    std::cout << "\n\nA * B: \n";
    std::cout << std::setw(COM_WIDTH) << "Predicted: " << mult << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Calculated: " << mult_res << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Equal: " << (mult == mult_res);
    std::cout << "\n\n(A * B)/B: \n";
    std::cout << std::setw(COM_WIDTH) << "Predicted: " << mult_div << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Calculated: " << mult_div_res << std::endl;
    std::cout << std::setw(COM_WIDTH) << "Equal: " << (mult_div == mult_div_res);
    std::cout << "\n--------------------------------" 
              << std::setfill('-') << std::setw(test_name.length()) 
              << '-' <<"--------------------------------\n\n";

    std::cout << std::setfill(' ');
}

namespace tests_512
{
	bool test_1()
	{
		LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x4D3C91C579C2C6216567A5241614B561ADDF76C4BB659E6FE7F65FF76A918C843F0458B3EF457BCD9022D78798A29462EC99C74E6674690267D3E9844251B39D";
		b = "0xDAF1ABDA4AD4D9FE3E36A529210C2AE99B905922FC0519798A26E351FE23AF375AD6BA288EE030B70DF0CE1CDF1E8B75BA56494DC6ED36B181814CD5783E6C81";
		sum = "0x1282E3D9FC497A01FA39E4A4D3720E04B496FCFE7B76AB7E9721D434968B53BBB99DB12DC7E25AC849E13A5A477C11FD8A6F0109C2D619FB3E9553659BA90201E";
		diff = "0x8db51a14d11213dcd8cf00050af77587edb0e25e409f7b09a230835a939222b31bd261749f9ab4e97dcdf695467bf712cdbc81ff6078cdaf19ad635135ecb8e4";
		diff.set_sign(-1);
		mult = "0x420E7E00B61E41A4992910FF7147F0D7DA534119BBD5BEE7EED2228604052A727147B4F01045272387643BC83E8AA54DD691149A58B77C0F3A39F7106AE22235D913D365494B7CC17BFE8294FAB72F34FA3230E1C9E8B145CCFEB672C73C922FF09ADFECFFCEB236A23A55C66904584EAC31CFA3B6A4DBC253D4E13BFAF7BE1D";
		mult_div = "0x4D3C91C579C2C6216567A5241614B561ADDF76C4BB659E6FE7F65FF76A918C843F0458B3EF457BCD9022D78798A29462EC99C74E6674690267D3E9844251B39D";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 1 (512)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
	}

    bool test_2()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0xA664199B424E606126A31B875E3D5E9E9C2E13D6995CC801E60C30247808A6EE01E78895E16EAD95354FE50A9396DA3D5BDB6327FBF7DE11871BF3D0143055EC";
		b = "0xD4DA433DBC99DE3D9F192F4B84000A628F00F01D10532B8299BE4987E001E2F23137039D7106217C58800406778F64750E949A6D229AC61FCD424632593C4735";
		sum = "0x17B3E5CD8FEE83E9EC5BC4AD2E23D69012B2F03F3A9AFF3847FCA79AC580A89E0331E8C335274CF118DCFE9110B263EB26A6FFD951E92A431545E3A026D6C9D21";
		diff = "0x2e7629a27a4b7ddc787613c425c2abc3f2d2dc4676f66380b3b2196367f93c042f4f7b078f9773e723301efbe3f88a37b2b9374526a2e80e46265262450bf149";
		diff.set_sign(-1);
		mult = "0x8A58C226B4429FFC0493D57D8B3EF3048C3C82269D5C2CC9E4F40A078C09107AD50C637D281E740790C76BC0D9DC9243D90DCE7BB8FA9FDA799D0C80BC2913E8B6B2E24CE7FCFD72F6D14F2539E68E80AB31B0265E16DAED3B4FA75091FC11E27C69FD3FAFEC5CB66CE5796E01D3F091D140CE0E6D33956B80F908F8C5263DDC";
		mult_div = "0xA664199B424E606126A31B875E3D5E9E9C2E13D6995CC801E60C30247808A6EE01E78895E16EAD95354FE50A9396DA3D5BDB6327FBF7DE11871BF3D0143055EC";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 2 (512)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }

    bool test_3()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x7723A9B9AFFCFCACFEF4537D2C587BA1E07EC2A27B9C907261F6461044DE2FEC26DA9BACDAC77063244D575EE788BB1145D7D09A94EC4B59859669CF8D86F454";
		b = "0xCE22515AE64F0FB5E6E33EF5D0D74AFE107BE2A91150D38A3AFCBC7608774631B56F41CDDD8A7D6A6C4170A4D17185E5C7578A27C2BD5816A62CD6D3E1E9266E";
		sum = "0x14545FB14964C0C62E5D79272FD2FC69FF0FAA54B8CED63FC9CF302864D55761DDC49DD7AB851EDCD908EC803B8FA40F70D2F5AC257A9A3702BC340A36F701AC2";
		diff = "0x56fea7a136521308e7eeeb78a47ecf5c2ffd200695b44317d9067665c39916458e94a62102c30d0747f41945e9e8cad4817fb98d2dd10cbd20966d045462321a";
        diff.set_sign(-1);
		mult = "0x5FEEAB2C8CB334B1A20D5136C4EFF15C344EA8F33FAD017396F80FFDC27BDA434DDF32BE81B2A9108B1F6AF16D02E98715B263C792C5275396A6A1F5157FB406F71ED4F5696B67465AEA4D24F25DAE054DFE56A1E02185CF63928B8598294979F8CF285D27B9AB9F13E1A514A7CB3B9E45A1EFCF8813DE6A608B4BFF0CB57418";
		mult_div = "0x7723A9B9AFFCFCACFEF4537D2C587BA1E07EC2A27B9C907261F6461044DE2FEC26DA9BACDAC77063244D575EE788BB1145D7D09A94EC4B59859669CF8D86F454";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 3 (512)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }

    bool test_4()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x94EDE1A444B9738ADF06CDB40DCAFA87B25A8BECA2D2262A53D8431A119405F0CBEFB83D2AD547CCE3AE74A8EC74A313C8BED20D4349D9EFBA356FE6E8AD89E2";
		b = "0x5BCC0B222EE17877C9EB60FA91632BC7A6E29D80F02CD3FE16B5C2A2231B43DB2B2D12F21B293AAF49FE1165CB7A21D12D6ACEC225285544B36BABD3F8B4DD8D";
		sum = "0xF0B9ECC6739AEC02A8F22EAE9F2E264F593D296D92FEFA286A8E05BC34AF49CBF71CCB2F45FE827C2DAC860EB7EEC4E4F629A0CF68722F346DA11BBAE162676F";
		diff = "0x3921D68215D7FB13151B6CB97C67CEC00B77EE6BB2A5522C3D228077EE78C215A0C2A54B0FAC0D1D99B0634320FA81429B54034B1E2184AB06C9C412EFF8AC55";
		mult = "0x3567433F4EE4A0539013C6D94CE053C39AF2B68268B48D20EEBB9596D07081615D9AFC9C19F6046B83AE7FBBE7C016A7BAD70B68016929BD0FB38F3AD28D71DF81B4D676D218B721CC480DC5659DA4EDEE1222744D9511EC55BAEEC07676513261E39333333EA5AA9B5A421B20241ED531E320E551F3697B6A654BE9DA850B7A";
		mult_div = "0x94EDE1A444B9738ADF06CDB40DCAFA87B25A8BECA2D2262A53D8431A119405F0CBEFB83D2AD547CCE3AE74A8EC74A313C8BED20D4349D9EFBA356FE6E8AD89E2";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 4 (512)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);

    }
}

namespace tests_1024
{
    bool test_1()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0xD4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB";
		b = "0x3A7EF2554E8940FA9B93B2A5E822CC7BB262F4A14159E4318CAE3ABF5AEB1022EC6D01DEFAB48B528868679D649B445A753684C13F6C3ADBAB059D635A2882090FC166EA9F0AAACD16A062149E4A0952F7FAAB14A0E9D3CB0BE9200DBD3B0342496421826919148E617AF1DB66978B1FCD28F8408506B79979CCBCC7F7E5FDE7";
		sum = "0x10F51035ED319BC50C0C4503B4D44872FC7DE7FC00F5DE863D6520E3906FC3E7E8761505118C918DB31AADBEA5A054B13A25F259CD47C1FAA7DB9B76F2DB450861BA26C4794E8E3BFBC2924DE45E47E5408536E3548A03591DA0556D595AB78C55149F45170F2CB7736A46976D1C09BFCE4DF6EAB040599AF235968F8070E25C2";
		diff = "0x9A531EB436073A5B899CEAEF7CFEEE386318967D8CAA2000BCF598BA51261E38AE874C932360023620DA0CAF90CEC25EB7F21C1A55A3A9F327AE7CA879634C73FC1F9E7256D38E258EE860B509506BAE185E180C06CC8DFBC23316BA1B357240BE81B14C9EC0A25A73AE85C0049185BD4A8D7E29F9F82A7C2FBFEF68174229F4";
		mult = "0x30A120B609DCBE28B09CA92E12DD29D77AE6400DC22B026AFB5FB945AAF62B57F4E48BD299261F02BBB35DD2495B5CD2713BF0E30192DAE1B334659160C8552423F0AD7FB82870920DF4E9B57980EAD2ADA9F3EF4B5D0718AB7F1053700395278998CB9AD48498D65150E3E837B0BB169D432B441424557061F838A17C65F90A31105F599BF69B87485BF9C70F51D37A417E476E372558C26782AC8C8F35C3D1227E851D8A72CD708700FD90C5E17F22C4EA15730345E56BD76F04B54580813CBE306B4404C6F34BCD9840D2911E6B3CF6DE3EE428C274EDF0A97335D8256DA26FCD67BA5450593A15F6B527ECE76FBBE20F7A882347614AF4B7FAF55086659D";
		mult_div = "0xD4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 1 (1024)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }

    bool test_2()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x87D6D58D3991D536544389CEFA72FD0EBED75B2EBDC2C79BC3717793108F0952011E7E2D7040FFFB32F10BEB8ED0A485026B6860020B230128A8222B0525A6888942FB01C537800BF25D6F021D4B99D3CBD6DF9055FA22F91A6CFC4FDFC408AEF78F6418D3CE4E20EC7888B61BAE3D73C27C257CCA905DE0353C3A7CFFD9FE15";
		b = "0x791EDB102DA183759979CEF70E1405AF14B98CD44357EADF6A8E35E49F99BB56CBD3F68897D6E05502ED1DE14EC46D04F96992C2D129737987E84E62371648B37633794016852A8CBFFCFDE06B17EC216AE8914D59E677A15A90361A594F0D1524A41AE63C59D343D4E522646722B0292DD7C85571AC9A84FDA6CD2D8DE307F6";
		sum = "0x100F5B09D673358ABEDBD58C6088702BDD390E803011AB27B2DFFAD77B028C4A8CCF274B60817E05035DE29CCDD951189FBD4FB22D334967AB090708D3C3BEF3BFF767441DBBCAA98B25A6CE2886385F536BF70DDAFE09A9A74FD326A391315C41C337EFF10282164C15DAB1A82D0ED9CF053EDD23C3CF86532E307AA8DBD060B";
		diff = "0xEB7FA7D0BF051C0BAC9BAD7EC5EF75FAA1DCE5A7A6ADCBC58E341AE70F54DFB354A87A4D86A1FA63003EE0A400C37800901D59D30E1AF87A0BFD3C8CE0F5DD5130F81C1AEB2557F32607121B233ADB260EE4E42FC13AB57BFDCC6358674FB99D2EB493297747ADD17936651B48B8D4A94A45D2758E3C35B37956D4F71F6F61F";
		mult = "0x4044EA5A25164D587B8B56B8E83AEA576AB448F5C6C2B8B94BE32DEAEE0205CB4EE7F38B011731DF3AB60DCD67B0F9A4F1321230E38C5E62214F6369BE12A3C730150C1E0A54BE2820E61B35F0184ED6667EF0CB132220C6CD75A02CDD45B310BC73398279BB3A3AAB14C1FDE28E7025AB2295B18B17F3EA87D18BB309EA04305E2C0A4F949A560C4F2AD3BC9C2F18564D173D2DD01673ACE42A9E0B157003469C835657AEBE14D382E88736B276C720A439D68897BAEF046878C0CB3595B42A337EB00EA1F3A7A5294F26AE99E700756C4EB7E2EA365A2EF7580A4955FDEBE0660CEDF5A4E56A01CB3B0C920BE8A03A69C4E6066B1D14AA8FA2090BAF0BBB2E";
		mult_div = "0x87D6D58D3991D536544389CEFA72FD0EBED75B2EBDC2C79BC3717793108F0952011E7E2D7040FFFB32F10BEB8ED0A485026B6860020B230128A8222B0525A6888942FB01C537800BF25D6F021D4B99D3CBD6DF9055FA22F91A6CFC4FDFC408AEF78F6418D3CE4E20EC7888B61BAE3D73C27C257CCA905DE0353C3A7CFFD9FE15";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 2 (1024)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }

    bool test_3()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x170076B15F9575D21DE39D5C429799BBCDDB867016DE2248E3CFDE73A4D70C8636A9E41ABE671E7B9FB4739A5FF64DF9D0D3A64E0C9B20BFE58F1C62B28477EE9FD202010BAC440ADF3CA016A32DB844F23DEC2AB93AE869A6262FC23C5CE419807CDBA930A5433884E3B34B22477289BD3A7712CDD4B4110BD9887E7428FDF7";
		b = "0x9D1C2D6E1591932F73C2F499C4E0A2E252DE828CDA7842CE0972C4101FE772B56C45C475EDDEDAEC2DBD13E375E02D2C149B69AB51FF3F94533CA34A815484EC86DACE936BDC62B5F3F9EB6F5BE6BD253E256181D35D7D63EE24459824D462C53676E3DFF98700415ADA65FDA7CBD3B3F359C817F52BEDA70C9DD85F68473C6";
		sum = "0x20D2398840EE8F05151FCCA5DEE5A3E9F3096E98E485A675C4670AB4A6D583B18D6E40621D450C2A629044D8975450CC921D5CE8C1BB14B92AC2E6975A99C03D683FAEEA426A0A363E7C3ECD98EC241746204242D670C03FE508741BBEAA2A45D3E449E7303DB33C9A9159AAFCC42FC4FC7013944D2772EB7CA366046AAD71BD";
		diff = "0xD2EB3DA7E3C5C9F26A76E12A6498F8DA8AD9E4749369E1C0338B232A2D8955ADFE587D35F8930CCDCD8A25C28984B270F89EFB3577B2CC6A05B522E0A6F2F9FD7645517D4EE7DDF7FFD015FAD6F4C729E5B96129C0510936743EB68BA0F9DED2D156D6B310CD3346F360CEB47CAB54E7E04DA914E81F5369B0FAAF87DA48A31";
		mult = "0xE1DD0ECBC0569D86631305BDF6715FFAE730E73504AC45962E5E8A4CCA50C2D7B5D56963ECBC7B581E820835EE00B1F6F4E43072F98CA5016E51A666B575C90A2FABBAC111435C86550EFDA9C4924D9A503777A0A1DE78C286E2FD73CAA861C3EA1E84053250CA2A235AF93C8AC105A08D3049909464394D6D16598FBAE735944C2D41C2E1F01C97428069CF3427FB8ED246CF15F163DFC385EDADF2EBE1A8900ECA0A6D6F4B3008FF1CB371BA03EFFEE3EFAF01E13673FCECA3A93CA89CBF8ABAEEF060B773F10B174A5E13BE3831195662FABDF07153F027C9617A67D65BCFB154EA70454CA6E8CDA2B118CF8A785AF2EDCBA40BE070FADCD57D8F26620A";
		mult_div = "0x170076B15F9575D21DE39D5C429799BBCDDB867016DE2248E3CFDE73A4D70C8636A9E41ABE671E7B9FB4739A5FF64DF9D0D3A64E0C9B20BFE58F1C62B28477EE9FD202010BAC440ADF3CA016A32DB844F23DEC2AB93AE869A6262FC23C5CE419807CDBA930A5433884E3B34B22477289BD3A7712CDD4B4110BD9887E7428FDF7";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 3 (1024)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }

    bool test_4()
    {
        LongInt a, b;

		LongInt sum, diff, mult, mult_div;
		
		// precalculated values
		a = "0x8703A1E982F278420C2D60CA7A0ED76C91855E3147B50357074A04EAF6515F07C1D8967674C7577D4112652E8135D145329F0DAE738F75C35004A154F1C43449DB87B6BE0F3EBF5B3BA1016F0A04A10C7EA76C3D30EEDB34B1E6E1009B3FF5C987FA313097485E6F8C78744E2F49DF62D13AD204E00F731BAE0E085C353D8D75";
		b = "0xB3CEBC5B7F698FF87B7BED132D299F68010583247B9C9792E809ED86C07B4D65C9E83AEE30897B0DAB7E5883EABE17B40B8F39267AC62377A6AFE0976AA0B81707282EB5FE59B66ED5EB1D3118CA3555F3AFCC28990AB016FE5B89D9159E6BB26151C923501F69629A0D75A6C06B8D0AA0364694DDCEDE35441E011347F85E62";
		sum = "0x13AD25E45025C083A87A94DDDA73876D4928AE155C3519AE9EF53F271B6CCAC6D8BC0D164A550D28AEC90BDB26BF3E8F93E2E46D4EE55993AF6B481EC5C64EC60E2AFE5740D9875CA118C1EA022CED66272573865C9F98B4BB0426AD9B0DE617BE94BFA53E767C7D22685E9F4EFB56C6D71711899BDDE5150F22C096F7D35EBD7";
		diff = "0x2ccb1a71fc7717b66f4e8c48b31ac7fb6f8024f333e7943be0bfe89bca29ee5e080fa477bbc223906a6bf3556988466ed8f02b780736adb456ab3f4278dc83cd2ba077f7ef1af7139a4a1bc20ec5944975085feb681bd4e24c74a8d87a5e75e8d95797f2b8d70af30d9501589121ada7cefb748ffdbf6b19960ff8b712bad0ed";
		diff.set_sign(-1);
		mult = "0x5ED492797CDB6D1CE4FE2BA7F7C7CC8CA220007237417066C8B77645FCA22793632F9630BB870AFA527B9A34A4D400B881ADE6CD421267BB820578EEE043A65029E3B808FCA0338883F91C54928E1BB8F1067CAEE97301250AF9C0A54302E25C5404D0D9AE7A2E9AFA450EA79D3CB1311B36BA0389FABE5D4CCCED13B6B777866EBA7A6E315EEF89AF3A7D91C8F20CD9A9DED3AB508991B855E5D1BE089D325324E1E8DAA1CE17B8895751E24BD2AFE25B22E8CD199DD97BE7D7931FEB9860693536E4F271EBF41F49A243D4179FA21102CBD941FDE6DFB0DA7A41967BDAB85A10D3923221A9E73FDAFF5026B93A7E8423D4C02D4FDA0D7B4D5DA96477D91CCA";
		mult_div = "0x8703A1E982F278420C2D60CA7A0ED76C91855E3147B50357074A04EAF6515F07C1D8967674C7577D4112652E8135D145329F0DAE738F75C35004A154F1C43449DB87B6BE0F3EBF5B3BA1016F0A04A10C7EA76C3D30EEDB34B1E6E1009B3FF5C987FA313097485E6F8C78744E2F49DF62D13AD204E00F731BAE0E085C353D8D75";

		LongInt sum_res, diff_res, mult_res, mult_div_res;

		sum_res = a + b;
        diff_res = a - b;
        mult_res = a * b;
        mult_div_res = (a * b) / b;

        print_test("TEST 4 (1024)" , a, b, sum, diff, mult, mult_div,
                    sum_res, diff_res, mult_res, mult_div_res);

        return (sum == sum_res) && (diff == diff_res) && (mult == mult_res) && (mult_div == mult_div_res);
    }
}