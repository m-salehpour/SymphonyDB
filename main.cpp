#include "sse/tosse.h"
#include "translation/tossmql.h"
#include "translation/tosomql.h"
#include "translation/to3mql.h"
#include "translation/checktype.h"
#include <fstream>
#include <iostream>


	extern int int_tmp_key;
	//extern set<string> set_bound_var;


int main(int argc, char** argv)
{
	
	std::ofstream ofs;
	std::string  line;
	std::string example_query = "";
	string outFile = "";//e.g.,home/ubuntu/EDBT/output
	bool type_flag = false;
    	if (argc == 3) 
    	{
		
		example_query  = argv[1];
		std::ifstream in(example_query);
		
		while (std::getline(in, line))
			example_query = line;
		if ( strcmp(argv[2], "-t") )
		{			
		//cout << "\n arg 2" << argv[2] << "\n";
				
		outFile = argv[2];
		ofs.open (outFile+"/MQL.js", std::ofstream::out | std::ofstream::trunc);
		}else
		type_flag = true;
	} else {
      	cout << "Usage: ./cppfile Input_SPARQL_query OutputFile_MQL\n";
      	return 1;
   	 }

	
	//BSBM 1
	//example_query = "PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  SELECT DISTINCT ?product ?label WHERE {   ?product rdfs:label ?label . ?product a %ProductType% . ?product bsbm:productFeature %ProductFeature1% .  ?product bsbm:productFeature %ProductFeature2% .  ?product bsbm:productPropertyNumeric1 ?value1 . 	FILTER (?value1 > %x%) 	} ORDER BY ?label LIMIT 10";

	//BSBM 2
	//example_query =	"PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX dc: <http://purl.org/dc/elements/1.1/> SELECT ?label ?comment ?producer ?productFeature ?propertyTextual1 ?propertyTextual2 ?propertyTextual3 ?propertyNumeric1 ?propertyNumeric2 ?propertyTextual4 ?propertyTextual5 ?propertyNumeric4 WHERE { %ProductXYZ% rdfs:label ?label .	%ProductXYZ% rdfs:comment ?comment .	%ProductXYZ% bsbm:producer ?p .	?p rdfs:label ?producer . %ProductXYZ% dc:publisher ?p . 	%ProductXYZ% bsbm:productFeature ?f .	?f rdfs:label ?productFeature .	%ProductXYZ% bsbm:productPropertyTextual1 ?propertyTextual1 .	%ProductXYZ% bsbm:productPropertyTextual2 ?propertyTextual2 . %ProductXYZ% bsbm:productPropertyTextual3 ?propertyTextual3 .	%ProductXYZ% bsbm:productPropertyNumeric1 ?propertyNumeric1 .	%ProductXYZ% bsbm:productPropertyNumeric2 ?propertyNumeric2 .	OPTIONAL { %ProductXYZ% bsbm:productPropertyTextual4 ?propertyTextual4  }  OPTIONAL { %ProductXYZ% bsbm:productPropertyTextual5 ?propertyTextual5  }  OPTIONAL { %ProductXYZ% bsbm:productPropertyNumeric4 ?propertyNumeric4 . }  }";		
	
	//BSBM 3
	//example_query =	" PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> SELECT ?product ?label WHERE { ?product rdfs:label ?label . ?product a %ProductType% .	?product bsbm:productFeature %ProductFeature1% .	?product bsbm:productPropertyNumeric1 ?p1 .	FILTER ( ?p1 > %x% ) 	?product bsbm:productPropertyNumeric3 ?p3 .	FILTER (?p3 < %y% ) OPTIONAL {  ?product bsbm:productFeature %ProductFeature2% . ?product rdfs:label ?testVar } FILTER (!bound(?testVar)) } ORDER BY ?label LIMIT 10";
	
	//BSBM 4 (Union)	
	
	//BSBM 5
	//example_query =	" PREFIX : <http://example.org/data/> SELECT * WHERE { ?x :p ?q . }";
	
	
	
	
	
	
	
	//example_query = "prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>  prefix allie: <http://purl.org/allie/ontology/201108#>  select distinct ?p ?n where {  ?p allie:hasshortformof ?n . ?n    rdfs:label \"mf\"@en . }";

	//example_query = "PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  PREFIX fd: <http://fishdelish.cs.man.ac.uk/rdf/vocab/resource1/>SELECT ?order ?family ?genus ?species ?name  WHERE   {         ?nameID fd:comnames_ComName %name3%  . ?nameID fd:comnames_ComName %name1%  .?nameID fd:comnames_ComName %name2%  .        ?nameID fd:comnames_C_Code ?ccode .                ?nameID fd:comnames_SpecCode ?x .     FILTER ( (!(?x <= (?f + %p1%))) )      .     ?x fd:species_Genus ?genus  .               ?x fd:species_Species %species%  . ?x fd:species_Species %species2%  . ?x fd:species_Species8 ?species  .              ?x fd:species_FamCode ?f  .               ?f fd:families_Family  ?family  .             ?f  fd:families_Order ?order  . FILTER ( (!(?family == (?ccode + %p2%))) ). } limit 2000";	
	
	//example_query = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  PREFIX bb: <http://www.owl-ontologies.com/Ontology1324312315.owl#>  PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  SELECT ?FirstName ?type1 ?type2   WHERE {  ?a pre1 ?h .  ?b pre2 ?a .  ?b pre3 ?c . ?c pre4 ?d . ?c pre5 ?e . ?c pre6 ?g . ?g pre7 ?h . ?e pre8 ?f . }";
	
	//example_query = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  PREFIX bb: <http://www.owl-ontologies.com/Ontology1324312315.owl#>  PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  SELECT ?FirstName ?type1 ?type2   WHERE { ?s p1 ?o1. optional{ ?o1 p2 ?o2}  ?o2 p3 ?o3 . Filter (?o3 < 10) ?s p4 \"mf\" . optional{ ?s p5 ?o4 . ?o4 p6 ?o5 . ?o4 p7 \"t\" . Filter (?o5 < 330) }  ?o5 p8 ?o6. ?o6 p9 \"Ann1\". ?o6 p9 \"Ann2\". ?o6 p10 ?o7.  }";
	
	//example_query = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  PREFIX bb: <http://www.owl-ontologies.com/Ontology1324312315.owl#>  PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  SELECT ?FirstName ?type1 ?type2   WHERE { ?s p1 ?o1. filter (?o1 >= 16) . optional{ ?s p2 \"mf\" .   ?s p3 ?o3 . Filter ( bound(?o3) )  } } ORDER BY ?o3 LIMIT 10";
	
	//example_query = "PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  PREFIX fd: <http://fishdelish.cs.man.ac.uk/rdf/vocab/resource1/>SELECT ?order ?family ?genus ?species ?name  WHERE   {         ?nameID fd:comnames_ComName ?name  .      optional{    ?nameID fd:comnames_C_Code ?ccode .  } .  FILTER ( (!(?ccode == (?name + %p1%))) || (!(?name <= (?ccode + %p1%)))  )           ?nameID fd:comnames_SpecCode ?x .               ?x fd:species_Genus ?genus  .               ?x fd:species_Species ?species  .               ?x fd:species_FamCode ?f  .               ?f fd:families_Family  ?family  .               ?f  fd:families_Order ?order  . FILTER ( (!(?x <= (?f + %p1%))) ) } ORDER BY desc(?ccode) asc(?f) ?name (?family) OFFSET 100 LIMIT 70";
	
	//example_query = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  PREFIX bb: <http://www.owl-ontologies.com/Ontology1324312315.owl#>  PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>  SELECT ?FamName ?FirstName   WHERE {  ?X rdf:type bb:Student .  ?Y rdf:type bb:Professor .  ?Z rdf:type bb:Evaluation .  ?D rdf:type bb:Department .  ?Z bb:performedByStudent ?X .  ?Z bb:evaluatedByProfessor ?Y .  ?Y bb:isAffiliatedWithDepartment ?D .  ?X bb:hasFamilyName ?FamName .  ?X bb:hasFirstName ?FirstName .  ?D bb:hasName \"Department0\"^^<http://www.w3.org/2001/XMLSchema#string> }";
	
	
	//example_query =	"PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> SELECT DISTINCT ?product ?label WHERE {  ?product rdfs:label ?label . ?product a %ProductType% . ?product bsbm:productFeature %ProductFeature1% .  ?product bsbm:productFeature %ProductFeature2% . ?product bsbm:productPropertyNumeric1 ?value1 . 	FILTER (?value1 > %x%) 	} ORDER BY ?label LIMIT 10";
	
	//example_query =	"PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> SELECT DISTINCT ?product ?label WHERE {   ?product rdfs:label ?label . ?product a %ProductType% . ?product bsbm:productFeature %ProductFeature1% .  ?product bsbm:productFeature %ProductFeature2% . ?product bsbm:productPropertyNumeric1 ?value1 . 	FILTER (?value1 > %x%) 	} ORDER BY ?label LIMIT 10";
	
	//example_query =	"PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> SELECT DISTINCT ?product ?label WHERE {  ?product rdfs:label ?label . ?product a %ProductType% . ?product a %ProductType2% . ?product a ?ProductType% . FILTER ( (!(?value1 == (?label + %p1%))) || (!(?value2 <= (?label + %p1%)))  )  ?product bsbm:productFeature %ProductFeature1% . optional{ ?product bsbm:productFeature %ProductFeature2% . ?product bsbm:productFeature %ProductFeature3% . ?product bsbm:productPropertyNumeric1 ?value1 . }   }  ORDER BY ?label LIMIT 10";
	
	//example_query =	"PREFIX bsbm-inst: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/instances/> PREFIX bsbm: <http://www4.wiwiss.fu-berlin.de/bizer/bsbm/v01/vocabulary/> PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#> PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> SELECT DISTINCT ?product ?label WHERE {  ?product rdfs:label ?label . filter (?label > 4) . optional { ?2product p2 ?n } ?product rdfs:label ?label2 . optional { ?product p2 ?n . ?product p2 ?n . } ?product rdfs:label ?label3 . ?product rdfs:label ?label4 . optional { ?product p2 ?n . ?product p2 ?n . }}  ORDER BY ?label LIMIT 10";
	
	
	//filter( ?value1 >= (!(?label - 170)) )  FILTER ( (!(?value1 <= (?label + %p1%))) )
	
	//auto get_namespace = tosse_obj.get_name_spaces(example_query);
	//auto get_projection_variables = tosse_obj.get_projection_variables(example_query);
	
	
	
	
	if (!type_flag)
	cout << "\n Original SPARQL Query:  \n" << example_query << "\n";

	tosse tosse_obj;
	

	
	auto get_triple_patterns_structs = tosse_obj.get_triple_patterns_structs(example_query);
	


	
	
	string opt = " select {";

	vector<string> optional_vec = tosse_obj.get_sparql_query_optional(example_query);

	//cout<< "  \n OPT:  "<<opt;
		for (int j=0; j < optional_vec.size(); j++)
			opt += optional_vec[j] + " . " ;
			
	opt += 	" }";
	
	
	std::vector<triple_pattern> get_optional_patterns_structs;	
	//cout<< "  \n OPT:  ";
	if (!optional_vec.empty())
	{	
		if (!type_flag)
		{
		cout << "\n" <<"################################"<< "\n";
                cout << "\n" <<"########--OPTIONAL--############"<< "\n";
		}
		get_optional_patterns_structs = tosse_obj.get_triple_patterns_structs(opt);
	}

	
	/*
	cout << "\n BEF SIZE: " << get_triple_patterns_structs.size() << "\n";
	if ( !get_optional_patterns_structs.empty() )
	get_triple_patterns_structs.insert(
	get_triple_patterns_structs.end(),
	get_optional_patterns_structs.begin(),
	get_optional_patterns_structs.end());
	cout << "\n Aft SIZE: " << get_triple_patterns_structs.size() << "\n";
	*/
	QueryTypes get_query_type = get_sparql_query_type(get_triple_patterns_structs);
	
	
	switch (get_query_type)
	{
		case (0):

			if (!type_flag) 
			ofs << sparql_to_t3_mql_translate(example_query, get_triple_patterns_structs, get_optional_patterns_structs) + "\n";
			else
			cout << "ss";
			//ofs <<  sparql_to_ss_mql_translate(example_query, get_triple_patterns_structs) + "\n";
			break;
			
		case (1):
			if (!type_flag) 
			ofs << sparql_to_t3_mql_translate(example_query, get_triple_patterns_structs, get_optional_patterns_structs) + "\n";
			else
			cout << "so";
	
						
			//ofs <<  sparql_to_so_mql_translate(example_query, get_triple_patterns_structs) + "\n";
			break;
			
		case (2):
			if (!type_flag) 
			ofs << sparql_to_t3_mql_translate(example_query, get_triple_patterns_structs, get_optional_patterns_structs) + "\n";
			else
			cout << "t3";
			break;
		
	}
	
	
	

return 0;
}
