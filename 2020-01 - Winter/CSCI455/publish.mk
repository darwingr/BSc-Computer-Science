# include publish.mk
# -include publish.mk       # no error if missing

# Guard against default rule
.PHONY: all
all:

handin       := $(project_label)-HANDIN.pdf

# The bare minimum to include this file.
ifndef project_label
$(error `project_label` has not been set in Makefile. \
		$$(project_label)-HANDIN.pdf = "$(handin)" )
else  # ifndef project_label


$(handin): $(ordered_docs) $(document_assets)
ifndef TITLE
	#-t "CSCI 455: Lab #11 Huffman Trees & B-Trees"
	$(warning No TITLE env variable set for document.)
else
	#$(info title is "CSCI 455: $(TITLE)")
endif #ifndef TITLE
ifndef ordered_docs
	$(warning No documents are specified for `ordered_docs`, $@ will have \
		no content.)
endif #ifndef ordered_docs
ifndef document_assets
	$(info Makefile variable `document_assets` is not defined)
	$(info >	No "make-able" asset dependencies are specified for $@)
endif #ifndef document_assets
	src2pdf -v \
		-t "CSCI 455: ${TITLE}" \
		-D "Winter 2020" \
		-o $@ \
		$(ordered_docs)

.PHONY: publish
publish: $(handin)


endif # ifndef project_label
