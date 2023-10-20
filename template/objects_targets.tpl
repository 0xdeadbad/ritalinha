$(OBJ_DIR)/%.o: $(${MODULE}_DIR)/%.c $(_${MODULE}_DEPS)
	$(MAKE) -C $(${MODULE}_DIR)
