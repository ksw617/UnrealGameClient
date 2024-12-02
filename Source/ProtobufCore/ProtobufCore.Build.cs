using System.IO;
using UnrealBuildTool;

public class ProtobufCore : ModuleRules
{ 
    public ProtobufCore(ReadOnlyTargetRules Target) : base(Target)
    {
        //모둘이 외부에서 가져온 라이브러리 라고 명시
        Type = ModuleType.External;

        //Protocol Buffers 라이브러리의 헤더 파일 위치를 컴파일러에게 알려줌
        PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));

        //라이브러리 파일의 위치를 링커가 찾을 수 있도록 지정
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "Win64", "libprotobuf.lib"));

        //Protocol Buffers 코드에서 RTTI를 사용하지 않도록 설정
        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");

    }
}