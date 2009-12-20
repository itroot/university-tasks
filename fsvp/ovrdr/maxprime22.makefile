# this makefile was automatically generated; do not edit 

TIMEOUT ?= 10

WHY=why -explain -locs maxprime22.loc 

GWHY=gwhy-bin -explain -locs maxprime22.loc 

CADULIB=/usr/local/lib/caduceus

CADULIBFILE=caduceus.why

COQTACTIC=intuition

COQDEP=coqdep -I `coqc -where`/user-contrib

.PHONY: all coq pvs simplify ergo cvcl harvey smtlib cvc3 z3 zenon

all: simplify/maxprime22_why.sx

coq: coq.depend coq/maxprime22_why.vo

coq/maxprime22_spec_why.v: why/maxprime22_spec.why
	@echo 'why -coq-v8 [...] why/maxprime22_spec.why' && $(WHY) -coq-v8 -dir coq -coq-preamble "Require Export Caduceus." $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why

coq/%_why.v: why/maxprime22_spec.why why/%.why
	@echo 'why -coq-v8 [...] why/$*.why' &&$(WHY) -coq-v8 -dir coq -coq-preamble "Require Export maxprime22_spec_why." -coq-tactic "$(COQTACTIC)" $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

coq/%.vo: coq/%.v
	coqc -I coq $<

pvs: pvs/maxprime22_spec_why.pvs pvs/maxprime22_why.pvs

pvs/maxprime22_spec_why.pvs: why/maxprime22_spec.why
	$(WHY) -pvs -dir pvs -pvs-preamble "importing why@why" $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why

pvs/%_why.pvs: pvs/maxprime22_spec_why.pvs why/%.why
	$(WHY) -pvs -dir pvs -pvs-preamble "importing maxprime22_spec_why" --lib-file ../../caduceus/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

pvs/caduceus_why.pvs:
	$(WHY) -pvs -dir pvs $(CADULIB)/why/$(CADULIBFILE)

isabelle: isabelle/maxprime22_why.thy isabelle/maxprime22_spec_why.thy

isabelle/%_spec_why.thy: why/%_spec.why
	$(WHY) -isabelle -dir isabelle -isabelle-base-theory caduceus_why $(CADULIB)/why/$(CADULIBFILE) why/$*_spec.why

isabelle/%_why.thy: isabelle/maxprime22_spec_why.thy why/%.why
	$(WHY) -isabelle -dir isabelle -isabelle-base-theory maxprime22_spec_why $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why
	cp -f /usr/local/lib/caduceus/isabelle/caduceus_why.thy isabelle/

simplify: simplify/maxprime22_why.sx
	@echo 'Running Simplify on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

simplify/%_why.sx: why/maxprime22_spec.why why/%.why
	@echo 'why -simplify [...] why/$*.why' && $(WHY) -simplify -dir  simplify $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

ergo: why/maxprime22_why.why
	@echo 'Running Ergo on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

why/%_why.sx: why/maxprime22_spec.why why/%.why
	@echo 'why -why [...] why/$*.why' && $(WHY) -why -dir why $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

project: why/maxprime22.wpr

why/%.wpr: why/maxprime22_ctx.why
	@echo 'why --project [...] why/$*.why' && $(WHY) --project -dir why $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

goals: why/maxprime22_ctx.why

why/%_ctx.why: why/maxprime22_spec.why why/%.why
	@echo 'why --multi-why [...] why/$*.why' && $(WHY) --multi-why -dir why $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

why/%_why.why: why/maxprime22_spec.why why/%.why
	@echo 'why -why [...] why/$*.why' && $(WHY) -why -dir why $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

cvcl: cvcl/maxprime22_why.cvc

	@echo 'Running CVC Lite on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

cvcl/%_why.cvc: why/maxprime22_spec.why why/%.why
	@echo 'why -cvcl [...] why/$*.why' && $(WHY) -cvcl --encoding sstrat -dir cvcl $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

harvey: harvey/maxprime22_why.rv
	@echo 'Running haRVey on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

harvey/%_why.rv: why/maxprime22_spec.why why/%.why
	@echo 'why -harvey [...] why/$*.why' && $(WHY) -harvey -dir harvey $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

zenon: zenon/maxprime22_why.znn
	@echo 'Running Zenon on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

zenon/%_why.znn: why/maxprime22_spec.why why/%.why
	@echo 'why -zenon [...] why/$*.why' && $(WHY) -zenon -dir zenon $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

smtlib: smtlib/maxprime22_why.smt
	@echo 'Running Z3 on proof obligations' && (why-dp -timeout $(TIMEOUT) $^)

smtlib/%_why.smt: why/maxprime22_spec.why why/%.why
	@echo 'why -smtlib [...] why/$*.why' && $(WHY) -smtlib --encoding sstrat -exp all   -dir smtlib $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

yices: smtlib/maxprime22_why.smt
	@echo 'Running Yices on proof obligations' && (why-dp -smt-solver yices -timeout $(TIMEOUT) $^)

z3: smtlib/maxprime22_why.smt
	@echo 'Running Z3 on proof obligations' && (why-dp -smt-solver z3 -timeout $(TIMEOUT) $^)

cvc3: smtlib/maxprime22_why.smt
	@echo 'Running CVC3 on proof obligations' && (why-dp -smt-solver cvc3 -timeout $(TIMEOUT) $^)

gui stat: maxprime22.stat

%.stat: why/maxprime22_spec.why why/%.why
	@echo 'gwhy-bin [...] why/$*.why' && $(GWHY) $(CADULIB)/why/$(CADULIBFILE) why/maxprime22_spec.why why/$*.why

-include maxprime22.depend

coq.depend: coq/maxprime22_spec_why.v coq/maxprime22_why.v
	-$(COQDEP) -I coq coq/maxprime22*_why.v > maxprime22.depend

clean:
	rm -f coq/*.vo

