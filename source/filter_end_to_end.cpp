#include "common.hpp"
#include "filter_end_to_end.hpp"

using namespace std;

unsigned int filter_end_to_end_fusions(fusions_t& fusions) {

	unsigned int remaining = 0;
	for (fusions_t::iterator i = fusions.begin(); i != fusions.end(); ++i) {
		if (i->second.filter != NULL)
			continue; // fusion has already been filtered

		if (i->second.discordant_mates + i->second.split_reads1 == 0 || // only filter breakpoints with low support
		    i->second.discordant_mates + i->second.split_reads2 == 0 ||
		    i->second.split_reads1 + i->second.split_reads2 == 0 ||
		    i->second.breakpoint_overlaps_both_genes() && (i->second.split_reads1 == 0 || i->second.split_reads2 == 0)) {
			if ((i->second.gene1->is_dummy || (i->second.gene1->strand == FORWARD && i->second.direction1 == UPSTREAM) || (i->second.gene1->strand == REVERSE && i->second.direction1 == DOWNSTREAM)) &&
			    (i->second.gene2->is_dummy || (i->second.gene2->strand == FORWARD && i->second.direction2 == UPSTREAM) || (i->second.gene2->strand == REVERSE && i->second.direction2 == DOWNSTREAM))) {
				i->second.filter = FILTERS.at("end_to_end");
				continue;
			}
		}

		++remaining;
	}

	return remaining;
}

